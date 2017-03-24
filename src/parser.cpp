#include "parser.hpp"

Parser::Parser() : comment_start('#'), quote_start('['), quote_end(']')
{
}

Parser::Parser(char comment_start) : quote_start('['), quote_end(']')
{
    setCommentStart(comment_start);
}

Parser::Parser(char quote_start, char quote_end) : comment_start('#')
{
    setQuoteStart(quote_start);
    setQuoteEnd(quote_end);
}

Parser::Parser(char comment_start, char quote_start, char quote_end)
{
    setCommentStart(comment_start);
    setQuoteStart(quote_start);
    setQuoteEnd(quote_end);
}

void Parser::setCommentStart(char c)
{
    if (!isSpace(c) || c != '\n')
        comment_start = c;
}

void Parser::setQuoteStart(char c)
{
    if (!isSpace(c) && !isEnd(c))
        quote_start = c;
}

void Parser::setQuoteEnd(char c)
{
    if (!isSpace(c) && !isEnd(c))
        quote_end = c;
}

char Parser::getCommentStart() const
{
    return (comment_start);
}

char Parser::getQuoteStart() const
{
    return (quote_start);
}

char Parser::getQuoteEnd() const
{
    return (quote_end);
}

bool Parser::parseLine(const std::string &line, std::string &key, std::string &value)
{
    size_t key_start,   value_start;
    size_t key_end,     value_end;

    if (!parseKeyword(line, 0, key_start, key_end))
        return (false);
    if (!parseKeyword(line, key_end + 2, value_start, value_end) ||
        line[key_end + 1] == comment_start)//in case there is only a word directly followed by a comment_start
        return (false);

    key.clear();
    value.clear();

    for (size_t i = key_start; i <= key_end; ++i)
         key += line[i];
    for (size_t i = value_start; i <= value_end; ++i)
        value += line[i];

    return (true);
}

bool Parser::parseKeyword(const std::string &str, size_t index, size_t &key_start, size_t &key_end)
{
    while (!isEnd(str[index]) && isSpace(str[index]))
        ++index;

    if (isEnd(str[index]))
        return (false);

    bool string_mode = str[index] == quote_start;
    key_start = index + (int)string_mode;
    ++index;

    if (!string_mode)
    {
        while (!isEnd(str[index]) && !isSpace(str[index]))
            ++index;

        key_end = index - 1;
        return (true);
    }
    else
    {
        while (!isEnd(str[index]) && str[index] != quote_end)
            ++index;
        key_end = index - 1;

        return(str[index] == quote_end && key_start != key_end);
    }
}

bool Parser::isSpace(char c)
{
    return (c == ' ' || c == '\t');
}

bool Parser::isEnd(char c)
{
    return (c == '\0' || c == '\n' || c == comment_start || c == EOF);
}

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

/*
** A line is compose of a keyword, spaces (or tabulations) and a value
** each line can start with spaces (or tabs) and finished with spaces and or comment
** (see COMMENT START).
** keyword and value can be compose of anything except space and tabulations.
** If you want to include them, keyword or value need to start with QUOTE_START
** and end with QUOTE_END but in this case, the current word can't contain them
** beside at the start and at the end (if QUOTE_START != QUOTE_END, QUOTE_START can
** be placed in the string without problem)
*/

class Parser
{
    public:
        //Default are : comment_start('#'), quote_start('['), quote_end(']')
                Parser();
                Parser(char comment_start);
                Parser(char quote_start, char quote_end);
                Parser(char comment_start, char quote_start, char quote_end);

        void    setCommentStart(char c);//can't be ' ', '\n', '\t'
        void    setQuoteStart(char c);//can't be comment_start, or ' ', '\n', '\t'
        void    setQuoteEnd(char c);//can't be comment_start, or ' ', '\n', '\t'
        char    getCommentStart() const;
        char    getQuoteStart() const;
        char    getQuoteEnd() const;

        bool    parseLine(const std::string &line, std::string &key, std::string &value);

    protected:

    private:
        bool    parseKeyword(const std::string &str, size_t index, size_t &key_start, size_t &key_end);
        bool    isSpace(char c);
        bool    isEnd(char c);

        char    comment_start;
        char    quote_start;
        char    quote_end;
};

#endif

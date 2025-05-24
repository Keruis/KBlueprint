module;
#include <list>
#include <map>
#include <string>

export module XmlParse;

namespace Utils {
    export class Xml {
    public:
        Xml();
        Xml(const char*);
        Xml(const std::string&);
        Xml(const Xml&);

        Xml& operator= (const Xml& other);
        Xml& operator [] (int);
        Xml& operator [] (const char*);
        Xml& operator [] (const std::string&);

        typedef std::list<Xml>::iterator iterator;
        iterator begin();
        iterator end();
        iterator erase(iterator);
        int size() const ;

        std::string name() const noexcept ;
        void name(const std::string&) noexcept ;
        std::string text() const noexcept ;
        void text(const std::string&) noexcept ;
        std::string attr(const std::string&) noexcept ;
        void attr(const std::string&, const std::string&) noexcept ;

        std::string str(int) const ;

        void append(const Xml&) noexcept ;

        void remove(int);
        void remove(const char*);
        void remove(const std::string&);

        void clear();

        bool load(const std::string&) noexcept ;
        bool save(const std::string&) noexcept ;
        bool parse(const std::string&) noexcept ;

    private:
        std::string* m_name;
        std::string* m_text;
        std::map<std::string, std::string>* m_attrs;
        std::list<Xml>* m_child;

        class Parser{
        public:
            Parser();
            bool loadFile(const std::string&) noexcept ;
            bool loadString(const std::string&) noexcept ;
            Xml Parse();

        private:
            void SkipWhiteSpace();
            bool ParseDeclaration();
            bool ParseComment();
            Xml ParseElement();
            std::string ParseElementName();
            std::string parseElementText();
            std::string parseElementAttrKey();
            std::string parseElementAttrVal();
        private:
            std::string m_str;
            int m_index;
        };
    };
}
#include "xml.h"
#include <string>
#include <map>
#include <fstream>
#include <list>
#include <sstream>


namespace Utils {
    Xml::Xml()
        : m_name(nullptr),
          m_text(nullptr),
          m_attrs(nullptr),
          m_child(nullptr) {

    }

    Xml::Xml(const char* name)
        : m_name(nullptr),
          m_text(nullptr),
          m_attrs(nullptr),
          m_child(nullptr) {
        m_name = new std::string(name);
    }

    Xml::Xml(const std::string& name)
        : m_name(nullptr),
          m_text(nullptr),
          m_attrs(nullptr),
          m_child(nullptr) {
        m_name = new std::string(name);
    }

    Xml::Xml(const Xml& other) {
        m_name = other.m_name;
        m_text = other.m_text;
        m_attrs = other.m_attrs;
        m_child = other.m_child;
    }

    Xml& Xml::operator= (const Xml& other){
        clear();
        m_name = other.m_name;
        m_text = other.m_text;
        m_attrs = other.m_attrs;
        m_child = other.m_child;
        return *this;
    }

    bool Xml::empty() {return m_child == nullptr;}
    Xml::iterator Xml::begin(){return m_child->begin();}
    Xml::iterator Xml::end(){return m_child->end();}
    Xml::iterator Xml::erase(iterator it){it->clear();return m_child->erase(it);}
    int Xml::size() const {return m_child->size();}
    std::string Xml::name() const noexcept {
        if(m_name == nullptr){return "";}
        return *m_name;
    }

    void Xml::name(const std::string& name) noexcept {
        if(m_name != nullptr){delete m_name;m_name = nullptr;}
        m_name = new std::string(name);
    }

    std::string Xml::text() const noexcept {
        if(m_text == nullptr){return "";}
        return *m_text;
    }

    void Xml::text(const std::string& name) noexcept {
        if(m_text != nullptr){delete m_text;m_text = nullptr;}
        m_text = new std::string(name);
    }

    std::string Xml::attr(const std::string& key) noexcept {
        if(m_attrs == nullptr){return "";}
        return (*m_attrs)[key];
    }

    void Xml::attr(const std::string& key, const std::string& value) noexcept {
        if(m_attrs == nullptr){m_attrs = new std::map<std::string, std::string>();}
        (*m_attrs)[key] = value;
    }

    std::string Xml::str(int level = 0) const {
        if (m_name == nullptr) {
            throw std::logic_error("element name is empty!");
        }

        std::stringstream ss;
        std::string indent(level * 2, ' ');

        ss << indent << "<" << *m_name;

        if (m_attrs != nullptr) {
            for (const auto& attr : *m_attrs) {
                ss << " " << attr.first << "=\"" << attr.second << "\"";}}

        bool hasChildren = (m_child != nullptr && !m_child->empty());
        bool hasText = (m_text != nullptr && !m_text->empty());

        if (!hasChildren && !hasText) {
            ss << " />\n";
        } else {
            ss << ">";

            if (hasText) {
                ss << *m_text;}

            if (hasChildren) {
                ss << "\n";
                for (const auto& child : *m_child) {
                    ss << child.str(level + 1); }
                ss << indent;}
            ss << "</" << *m_name << ">\n";}
        return ss.str();
    }

    void Xml::append(const Xml& child) noexcept {
        if(m_child == nullptr){m_child = new std::list<Xml>();}
        m_child->push_back(child);
    }

    Xml& Xml::operator [] (int index){
        if(index < 0){
            throw std::logic_error("index less than zwro");
        }
        if(m_child == nullptr){
            m_child = new std::list<Xml>();
        }
        int size = m_child->size();
        if(index >= 0 && index < size){
            auto it = m_child->begin();
            for(int i = 0; i<index; i++){
                it++;
            }
            return *it;
        }
        if(index >= size){
            for(int i = size; i<= index; i++){
                m_child->push_back(Xml());
            }
        }
        return m_child->back();
    }

    Xml& Xml::operator [] (const char* name){
        return (*this)[std::string(name)];
    }

    Xml& Xml::operator [] (const std::string& name){
        if(m_child == nullptr){
            m_child = new std::list<Xml>();
        }
        for(auto it = m_child->begin(); it != m_child->end(); it++){
            if(it->name() == name){
                return *it;
            }
        }
        m_child->push_back(Xml(name));
        return m_child->back();
    }

    void Xml::remove(int index){
        if(m_child == nullptr) {
            return;
        }
        int size = m_child->size();
        if(index < 0 || index >= size){
            return;
        }
        auto it = m_child->begin();
        for(int i = 0; i< index; i++){
            it++;
        }
        it->clear();
        m_child->erase(it);
    }

    void Xml::remove(const char* name){remove(std::string(name));}
    void Xml::remove(const std::string& name){
        if(m_child == nullptr){
            return;
        }
        for(auto it = m_child->begin(); it != m_child->end();){
            if(it->name() == name){
                it->clear();
                it = m_child->erase(it);
            }else{
                it++;
            }
        }
    }

    void Xml::clear(){
        if(m_name != nullptr){
            delete m_name;m_name = nullptr;
        }
        if(m_text != nullptr){
            delete m_text;m_text = nullptr;
        }
        if(m_attrs != nullptr){
            delete m_attrs;m_attrs = nullptr;
        }
        if(m_child != nullptr){
            for(auto it = m_child->begin(); it != m_child->end(); it++){
                it->clear();}
            delete m_child;m_child = nullptr;
        }
    }

    bool Xml::load(const std::string& filename) noexcept {
        Parser parse;
        if(!parse.loadFile(filename)){return false;}
        *this = parse.Parse();
        return true;
    }

    bool Xml::save(const std::string& filename) noexcept {
        std::ofstream fileout(filename);
        if(fileout.fail()){return false;}
        fileout << str();fileout.close();
        return true;
    }

    bool Xml::parse(const std::string& str) noexcept {
        Parser parse;
        if(!parse.loadString(str)){return false;}
        *this = parse.Parse();
        return true;
    }



    Xml::Parser::Parser() : m_str(""), m_index(0){}
    bool Xml::Parser::loadFile(const std::string& filename) noexcept {
        std::ifstream file(filename);
        if(file.fail()){return false;}
        std::stringstream ss;
        ss << file.rdbuf();m_str = ss.str();m_index = 0;
        return true;
    }

    bool Xml::Parser::loadString(const std::string& str) noexcept {
        m_str = str;m_index = 0;return true;
    }

    Xml Xml::Parser::Parse() {
        SkipWhiteSpace();
        if(m_str.compare(m_index,5,"<?xml") == 0){
            if(!ParseDeclaration()){
                throw std::logic_error("parse declearation error");
            }
        }
        SkipWhiteSpace();
        while(m_str.compare(m_index,4,"<!--") == 0){
            if(!ParseComment()){
                throw std::logic_error("parse comment error");}
            SkipWhiteSpace();
        }
        if(m_str[m_index] == '<' && (isalpha(m_str[m_index+1]) || m_str[m_index+1] == '_')){
            return ParseElement();
        }
        throw std::logic_error("parse element error");
    }

    void Xml::Parser::SkipWhiteSpace(){
        while(m_str[m_index] == ' ' || m_str[m_index] == '\r' || m_str[m_index] == '\n' || m_str[m_index] == '\t'){
            m_index++;
        }
    }

    bool Xml::Parser::ParseDeclaration(){
        if(m_str.compare(m_index,5,"<?xml") != 0){return false;}
        m_index += 5;
        std::size_t pos = m_str.find("?>",m_index);
        if(pos == std::string::npos){return false;}
        m_index = pos + 2;
        return true;
    }
    bool Xml::Parser::ParseComment(){
        if(m_str.compare(m_index,4,"<!--") != 0){return false;}
        m_index += 4;
        std::size_t pos = m_str.find("-->",m_index);
        if(pos == std::string::npos){return false;}
        m_index = pos +3;
        return true;
    }

    Xml Xml::Parser::ParseElement(){
        Xml elem;
        m_index++;
        SkipWhiteSpace();
        const std::string& name = ParseElementName();
        elem.name(name);
        while(m_str[m_index] != '\0'){
            SkipWhiteSpace();
            if(m_str[m_index] == '/'){
                if(m_str[m_index+1] == '>'){
                    m_index += 2;
                    break;
                } else {
                    throw std::logic_error("xml empty element is error");
                }
            } else if (m_str[m_index] == '>'){
                m_index++;
                std::string text = parseElementText();
                if (text != ""){
                    elem.text(text);
                }
            } else if (m_str[m_index] == '<'){
                if (m_str[m_index+1] == '/'){
                    std::string end_tag = "</" + name + ">";
                    std::size_t pos = m_str.find(end_tag,m_index);
                    if(pos == std::string::npos){
                        throw std::logic_error("xml element " + name + "end tag not found");
                    }
                    m_index = (pos + end_tag.size());
                    break;
                } else if (m_str.compare(m_index,4,"<!--") == 0){
                    if(!ParseComment()){
                        throw std::logic_error("xml comment is error");
                    }
                } else {
                    elem.append(ParseElement());
                }
            } else {
                std::string key = parseElementAttrKey();
                SkipWhiteSpace();
                if(m_str[m_index] != '='){
                    throw std::logic_error("xml element attr is error");
                }
                m_index++;
                SkipWhiteSpace();
                std::string val = parseElementAttrVal();
                elem.attr(key,val);
            }
        }
        return elem;
    }

    std::string Xml::Parser::ParseElementName(){
        int pos = m_index;
        if(isalpha(m_str[m_index]) || (m_str[m_index] == '_')){
            m_index++;
            while(isalnum(m_str[m_index]) || (m_str[m_index] == '_') || (m_str[m_index] == '-') || (m_str[m_index] == ':') || (m_str[m_index] == '.')){
                m_index++;
            }
        }
        return m_str.substr(pos, m_index - pos);
    }

    std::string Xml::Parser::parseElementText(){
            int pos = m_index;
            while(m_str[m_index] != '<'){m_index++;
        }
        return m_str.substr(pos,m_index - pos);
    }

    std::string Xml::Parser::parseElementAttrKey(){
        int pos = m_index;
        if(isalpha(m_str[m_index]) || (m_str[m_index] == '_')){
            m_index++;
            while(isalnum(m_str[m_index]) || (m_str[m_index] == '_') || (m_str[m_index] == '-') || (m_str[m_index] == ':')){
                m_index++;
            }
        }
        return m_str.substr(pos, m_index - pos);
    }

    std::string Xml::Parser::parseElementAttrVal(){
        if(m_str[m_index] != '"'){
            throw std::logic_error("xml element attr value should be in double quotes");
        }
        m_index++;
        int pos = m_index;
        while(m_str[m_index] != '"'){
            m_index++;
        }
        m_index++;
        return m_str.substr(pos, m_index - pos - 1);
    }
}
#ifndef WEB_PAGE_HPP
#define WEB_PAGE_HPP

#include <iostream>
#include <string>
#include <memory>

#include <Wt/WContainerWidget.h>



class WebPage
{
    public:
        WebPage();
        WebPage(const std::string& internalPath);
        WebPage(const WebPage& obj) = delete;
        WebPage(WebPage&& obj);
        virtual ~WebPage() = default;

        WebPage& operator=(const WebPage& obj) = delete;
        WebPage& operator=(WebPage&& obj);

        virtual void render(Wt::WContainerWidget& content) = 0;

        std::string getInternalPath() const;
        void setInternalPath(const std::string& internalPath);


    private:
        std::unique_ptr<std::string> internalPath;
};


WebPage::WebPage()
{
    internalPath = std::make_unique<std::string>();
}


WebPage::WebPage(const std::string& internalPath)
{
    this->internalPath = std::make_unique<std::string>(internalPath);
}


WebPage::WebPage(WebPage&& obj)
{
    *internalPath = std::move(*obj.internalPath);
}


WebPage& WebPage::operator=(WebPage&& obj)
{
    *internalPath = std::move(*obj.internalPath);
    return *this;
}


std::string WebPage::getInternalPath() const
{
    return *internalPath;
}


void WebPage::setInternalPath(const std::string& internalPath)
{
    *this->internalPath = internalPath;
}



#endif  // WEB_PAGE_HPP
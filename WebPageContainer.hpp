#ifndef WEB_PAGE_CONTAINER_HPP
#define WEB_PAGE_CONTAINER_HPP

#include "WebPage.hpp"

#include <cinttypes>
#include <vector>

#include <Wt/WApplication.h>



class WebPageContainer
{
    public:
        WebPageContainer() = default;
        WebPageContainer(std::unique_ptr<Wt::WContainerWidget> content);
        WebPageContainer(Wt::WContainerWidget* content);
        WebPageContainer(const WebPageContainer& obj) = delete;
        WebPageContainer(WebPageContainer&& obj) = delete;
        virtual ~WebPageContainer() = default;

        WebPageContainer& operator=(const WebPageContainer& obj) = delete;
        WebPageContainer& operator=(WebPageContainer&& obj) = delete;

        static WebPageContainer* instance();

        Wt::WContainerWidget* getContent() const;
        void setContent(std::unique_ptr<Wt::WContainerWidget> content);
        void setContent(Wt::WContainerWidget* content);
        bool isContent() const;
        bool isContentPtr() const;

        void reset();
        template<typename PageType> PageType* addPage(const std::string& internalPath);
        void removePage(const WebPage& page);
        void renderPage(WebPage& page);
        void renderPage(const std::string& internalPath);
        void clearPage();
        WebPage* getPage(const std::string& internalPath);
        template<typename PageType> PageType* getPage(const std::string& internalPath);
        std::vector<std::unique_ptr<WebPage>>* getPages();
        bool isPage(const WebPage& page, std::size_t* position = nullptr) const;
        std::size_t pageCount() const;


    private:
        static WebPageContainer* thisInstance;
        std::vector<std::unique_ptr<WebPage>> pages;
        std::unique_ptr<Wt::WContainerWidget> content;
        Wt::WContainerWidget* contentPtr = nullptr;
};


WebPageContainer* WebPageContainer::thisInstance = nullptr;


WebPageContainer::WebPageContainer(std::unique_ptr<Wt::WContainerWidget> content)
{
    this->content = std::move(content);
    thisInstance = this;
}


WebPageContainer::WebPageContainer(Wt::WContainerWidget* content)
{
    contentPtr = content;
    thisInstance = this;
}


WebPageContainer* WebPageContainer::instance()
{
    return thisInstance;
}


void WebPageContainer::reset()
{
    pages.clear();
    content.reset();
    contentPtr = nullptr;
}


Wt::WContainerWidget* WebPageContainer::getContent() const
{
    if (contentPtr != nullptr) { return contentPtr; }
    else if (content.get() != nullptr) { return content.get(); }
    return nullptr;
}


void WebPageContainer::setContent(std::unique_ptr<Wt::WContainerWidget> content)
{
    this->content = std::move(content);
}


void WebPageContainer::setContent(Wt::WContainerWidget* content)
{
    contentPtr = content;
}


bool WebPageContainer::isContent() const
{
    return (content.get() != nullptr);
}


bool WebPageContainer::isContentPtr() const
{
    return (contentPtr != nullptr);
}


void WebPageContainer::renderPage(WebPage& page)
{
    if (isPage(page) == true)
    {
        if (contentPtr != nullptr) { page.render(*contentPtr); }
        else if (content.get() != nullptr) { page.render(*content); }
        return;
    }
}


void WebPageContainer::renderPage(const std::string& internalPath)
{
    for (std::unique_ptr<WebPage>& singlePage : pages)
    {
        if (singlePage->getInternalPath() == internalPath)
        {
            if (contentPtr != nullptr) { singlePage->render(*contentPtr); }
            else if (content.get() != nullptr) { singlePage->render(*content); }
            return;
        }
    }
}


void WebPageContainer::clearPage()
{
    if (contentPtr != nullptr) { contentPtr->clear(); }
    else if (content.get() != nullptr) { content->clear(); }
}


template<typename PageType>
PageType* WebPageContainer::addPage(const std::string& internalPath)
{
    pages.push_back(std::make_unique<PageType>(internalPath));
    return dynamic_cast<PageType*>(pages.at(pages.size() - 1).get());
}


void WebPageContainer::removePage(const WebPage& page)
{
    std::size_t position = 0;
    if (isPage(page, &position) == true)
    {
        pages.erase(pages.begin() + position);
    }
}


WebPage* WebPageContainer::getPage(const std::string& internalPath)
{
    for (std::unique_ptr<WebPage>& singlePage : pages)
    {
        if (singlePage->getInternalPath() == internalPath) { return singlePage.get(); }
    }

    return nullptr;
}


template<typename PageType>
PageType* WebPageContainer::getPage(const std::string& internalPath)
{
    for (std::unique_ptr<WebPage>& singlePage : pages)
    {
        if (singlePage->getInternalPath() == internalPath) { return dynamic_cast<PageType*>(singlePage.get()); }
    }

    return nullptr;
}


std::vector<std::unique_ptr<WebPage>>* WebPageContainer::getPages()
{
    return &pages;
}


bool WebPageContainer::isPage(const WebPage& page, std::size_t* position) const
{
    if (position != nullptr)
    {
        for (const std::unique_ptr<WebPage>& singlePage : pages)
        {
            if (singlePage.get() == &page) { return true; }
            else { *position += 1; }
        }

        *position = 0;
    }

    else
    {
        for (const std::unique_ptr<WebPage>&singlePage : pages)
        {
            if (singlePage.get() == &page) { return true; }
        }
    }

    return false;
}


std::size_t WebPageContainer::pageCount() const
{
    return pages.size();
}



#endif  // WEB_PAGE_CONTAINER_HPP

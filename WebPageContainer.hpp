#ifndef WEB_PAGE_CONTAINER_HPP
#define WEB_PAGE_CONTAINER_HPP

#include "WebPage.hpp"
#include <cinttypes>
#include <vector>
#include <iterator>



class WebPageContainer
{
    public:
        enum class ErrorType
        {
            NO_RENDER_CONTAINER,
            NO_PAGE,
            PAGE_EXISTS,
            OK
        };

        WebPageContainer() = default;
        WebPageContainer(Wt::WContainerWidget* container);
        WebPageContainer(const WebPageContainer& obj) = delete;
        WebPageContainer(WebPageContainer&& obj);
        virtual ~WebPageContainer() = default;
        
        WebPageContainer& operator=(const WebPageContainer& obj) = delete;
        WebPageContainer& operator=(WebPageContainer&& obj);

        void reset();
        ErrorType addPage(std::unique_ptr<WebPage> page);
        ErrorType removePage(const WebPage* page);
        ErrorType removePage(const std::string& internalPath);
        
        ErrorType redirect(WebPage* page);
        ErrorType redirect(const std::string& internalPath);
        
        Wt::WContainerWidget* renderContainer();
        const Wt::WContainerWidget* renderContainer() const;
        void setRenderContainer(Wt::WContainerWidget* container);
        WebPage* getPage(const std::string& internalPath);
        const WebPage* getPage(const std::string& internalPath) const;
        const std::vector<std::unique_ptr<WebPage>>& getPages() const;
        WebPage* renderedPage();
        const WebPage* renderedPage() const;
        
        std::size_t pageCount() const;
        bool isRenderContainer() const;
        bool isRenderedPage() const;
        bool isPage(const WebPage* page) const;
    	bool isPage(const std::string& internalPath) const;

        static const char* getErrorMessage(const ErrorType& error);


    private:
        void log(const ErrorType& error);
        std::vector<std::unique_ptr<WebPage>>::iterator findPage(const std::string& internalPath);
        std::vector<std::unique_ptr<WebPage>>::const_iterator findPage(const std::string& internalPath) const;

        std::vector<std::unique_ptr<WebPage>> pages_;
        Wt::WContainerWidget* renderContainer_ = nullptr;
        WebPage* renderedPage_ = nullptr;
        std::size_t renderedPageIndex_ = 0;

        static const std::string WPC_LOG_ERROR;
        static const std::string WPC_LOG_INFO;
};


inline WebPageContainer::ErrorType WebPageContainer::removePage(const WebPage* page)
{
    return removePage(page->internalPath());
}


inline WebPageContainer::ErrorType WebPageContainer::redirect(WebPage* page)
{
    return redirect(page->internalPath());
}


inline Wt::WContainerWidget* WebPageContainer::renderContainer()
{
    return renderContainer_;
}


inline const Wt::WContainerWidget* WebPageContainer::renderContainer() const
{
    return renderContainer_;
}


inline void WebPageContainer::setRenderContainer(Wt::WContainerWidget* container)
{
    renderContainer_ = container;
}


inline WebPage* WebPageContainer::getPage(const std::string& internalPath)
{
    return (*findPage(internalPath)).get();
}


inline const WebPage* WebPageContainer::getPage(const std::string& internalPath) const
{
    return (*findPage(internalPath)).get();
}


inline const std::vector<std::unique_ptr<WebPage>>& WebPageContainer::getPages() const
{
	return pages_;
}


inline WebPage* WebPageContainer::renderedPage()
{
    return renderedPage_;
}


inline const WebPage* WebPageContainer::renderedPage() const
{
    return renderedPage_;
}


inline std::size_t WebPageContainer::pageCount() const
{
    return pages_.size();
}


inline bool WebPageContainer::isRenderContainer() const
{
    return static_cast<bool>(renderContainer_);
}


inline bool WebPageContainer::isRenderedPage() const
{
    return static_cast<bool>(renderedPage_);
}


inline bool WebPageContainer::isPage(const WebPage* page) const
{
    return isPage(page->internalPath()); 
}


#endif  // WEB_PAGE_CONTAINER_HPP

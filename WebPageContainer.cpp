#include "WebPageContainer.hpp"
#include <Wt/WLogger.h>



const std::string WebPageContainer::WPC_LOG_ERROR = "wpc_error";
const std::string WebPageContainer::WPC_LOG_INFO = "wpc_info";


WebPageContainer::WebPageContainer(Wt::WContainerWidget* container) :
    renderContainer_(container)
{   

}


WebPageContainer::WebPageContainer(WebPageContainer&& obj) :
    pages_(std::move(obj.pages_)),
    renderContainer_(obj.renderContainer_),
    renderedPage_(obj.renderedPage_),
    renderedPageIndex_(obj.renderedPageIndex_)
{
    obj.reset();
}


WebPageContainer& WebPageContainer::operator=(WebPageContainer&& obj)
{
    if (&obj != this)
    {
        pages_ = std::move(obj.pages_);
        renderContainer_ = obj.renderContainer_;
        renderedPage_ = obj.renderedPage_;
        renderedPageIndex_ = obj.renderedPageIndex_;
        obj.reset();
    }

    return *this;
}


void WebPageContainer::reset()
{   
    pages_.clear();
    renderContainer_ = nullptr;
	renderedPage_ = nullptr;
    renderedPageIndex_ = 0;
}


WebPageContainer::ErrorType WebPageContainer::addPage(std::unique_ptr<WebPage> page)
{   
    ErrorType error;
	if (isPage(page->internalPath()) == false) {
        pages_.push_back(std::move(page));
        error = ErrorType::OK;
    }
    else { 
        error = ErrorType::PAGE_EXISTS;
        log(error);
    }

    return error;
}


WebPageContainer::ErrorType WebPageContainer::removePage(const std::string& internalPath)
{
    ErrorType error;
    auto page = findPage(internalPath);

    if (page != pages_.end())
    {
        pages_.erase(page);
        if (renderedPage_->internalPath() == internalPath)
        {
            renderContainer_->removeWidget(renderedPage_);
            renderedPage_ = nullptr;
            renderedPageIndex_ = 0;
        }

        error = ErrorType::OK;
    }

    else {
        error = ErrorType::NO_PAGE;
        log(error);
    }

    return error;
}


WebPageContainer::ErrorType WebPageContainer::redirect(const std::string& internalPath)
{
    ErrorType error;
    auto page = findPage(internalPath);

    if (page != pages_.end())
    {
        if (isRenderContainer())
        {
            if (isRenderedPage()) {
                pages_.at(renderedPageIndex_) = renderContainer_->removeWidget(renderedPage_);
            }

            renderedPageIndex_ = std::distance(pages_.begin(), page);
            renderedPage_ = (*page).get();

            if (renderedPage_->isRendered() == false) { renderedPage_->render(); }
            renderContainer_->addWidget(std::move(*page));

            error = ErrorType::OK;
        }

        else {
            error = ErrorType::NO_RENDER_CONTAINER;
            log(error);
        }
    }

    else {
        error = ErrorType::NO_PAGE;
        log(error);
    }

    return error;
}


bool WebPageContainer::isPage(const std::string& internalPath) const
{
    return (findPage(internalPath) != pages_.end());
}


void WebPageContainer::log(const ErrorType& error)
{
    const std::string log_type = [&error]()
    {
        if (error == ErrorType::OK) { return WPC_LOG_INFO; }
        return WPC_LOG_ERROR;
    }();

    Wt::log(log_type) << getErrorMessage(error);
}


const char* WebPageContainer::getErrorMessage(const ErrorType& error)
{
	static const char* erorr_logs[] = 
	{
		"wpc: No render container",
		"wpc: Page not in container",
		"wpc: Page already in container",
        "wpc: OK"
	};
	
	return erorr_logs[static_cast<std::size_t>(error)];
}


std::vector<std::unique_ptr<WebPage>>::iterator WebPageContainer::findPage(const std::string& internalPath)
{
    if (internalPath.empty() == false && pages_.empty() == false)
    {
        if (isRenderedPage() && 
            renderedPage_->internalPath() == internalPath) { 
            return (pages_.begin() + renderedPageIndex_); 
        }

        for (auto page = pages_.begin(); page != pages_.end(); page += 1)
        {
            if ((*page).get() != nullptr && (*page)->isInternalPath() && 
                (*page)->internalPath() == internalPath) { return page; }
        }
    }

    return pages_.end();
}


std::vector<std::unique_ptr<WebPage>>::const_iterator WebPageContainer::findPage(const std::string& internalPath) const
{
    if (internalPath.empty() == false && pages_.empty() == false)
    {
        if (isRenderedPage() && 
            renderedPage_->internalPath() == internalPath) { 
            return (pages_.begin() + renderedPageIndex_); 
        }

        for (auto page = pages_.begin(); page != pages_.end(); page += 1)
        {
            if ((*page).get() != nullptr && (*page)->isInternalPath() && 
                (*page)->internalPath() == internalPath) { return page; }
        }
    }

    return pages_.end();
}

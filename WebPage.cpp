#include "WebPage.hpp"



WebPage::WebPage(const std::string& internalPath) :
    internalPath_(internalPath), 
    isInternalPath_(!internalPath.empty())
{

}


WebPage::WebPage(WebPage&& obj) :
    internalPath_(std::move(obj.internalPath_)),
    isInternalPath_(obj.isInternalPath_)
{
    obj.isInternalPath_ = false;
}


WebPage& WebPage::operator=(WebPage&& obj)
{
    if (&obj != this)
    {
        internalPath_ = std::move(obj.internalPath_);
        isInternalPath_ = obj.isInternalPath_;
        obj.isInternalPath_ = false;
    }

    return *this;
}


bool WebPage::operator==(const WebPage& obj)
{
    if (isInternalPath_ == false || obj.isInternalPath_ == false) { return false; }
	return (internalPath_ == obj.internalPath_);
}


bool WebPage::operator!=(const WebPage& obj)
{
    if (isInternalPath_ == false || obj.isInternalPath_ == false) { return true; }
	return (internalPath_ != obj.internalPath_);
}


void WebPage::reset()
{
    internalPath_.clear();
    isInternalPath_ = false;
}


void WebPage::setInternalPath(const std::string& internalPath)
{
    internalPath_ = internalPath;
    isInternalPath_ = !internalPath_.empty();
}

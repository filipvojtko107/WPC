#ifndef WEB_PAGE_HPP
#define WEB_PAGE_HPP

#include <string>
#include <Wt/WContainerWidget.h>



class WebPage : public Wt::WContainerWidget
{
    public:
        WebPage() = default;
        WebPage(const std::string& internalPath);
        WebPage(const WebPage& obj) = delete;
        WebPage(WebPage&& obj);
        virtual ~WebPage() = default;

        WebPage& operator=(const WebPage& obj) = delete;
        WebPage& operator=(WebPage&& obj);
        
        bool operator==(const WebPage& obj);
        bool operator!=(const WebPage& obj);

        virtual void render() = 0;
        virtual void reset();

        virtual bool isRendered() const;
        std::string internalPath() const;
        void setInternalPath(const std::string& internalPath);
        bool isInternalPath() const;


    private:
    	std::string internalPath_;
        bool isInternalPath_ = false;
};


inline bool WebPage::isRendered() const
{
    return static_cast<bool>(this->count());
}


inline std::string WebPage::internalPath() const
{
    return internalPath_;
}


inline bool WebPage::isInternalPath() const
{
    return isInternalPath_;
}


#endif  // WEB_PAGE_HPP
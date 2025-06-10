#ifndef APPPAGEVIEW_HPP
#define APPPAGEVIEW_HPP

#include <gui_generated/apppage_screen/AppPageViewBase.hpp>
#include <gui/apppage_screen/AppPagePresenter.hpp>

class AppPageView : public AppPageViewBase
{
public:
    AppPageView();
    virtual ~AppPageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // APPPAGEVIEW_HPP

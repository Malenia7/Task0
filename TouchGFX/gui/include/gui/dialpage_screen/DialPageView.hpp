#ifndef DIALPAGEVIEW_HPP
#define DIALPAGEVIEW_HPP

#include <gui_generated/dialpage_screen/DialPageViewBase.hpp>
#include <gui/dialpage_screen/DialPagePresenter.hpp>

class DialPageView : public DialPageViewBase
{
public:
    DialPageView();
    virtual ~DialPageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DIALPAGEVIEW_HPP

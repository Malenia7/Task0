#ifndef DIALPAGEPRESENTER_HPP
#define DIALPAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DialPageView;

class DialPagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DialPagePresenter(DialPageView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~DialPagePresenter() {};

private:
    DialPagePresenter();

    DialPageView& view;
};

#endif // DIALPAGEPRESENTER_HPP

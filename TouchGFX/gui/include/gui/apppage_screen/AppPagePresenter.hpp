#ifndef APPPAGEPRESENTER_HPP
#define APPPAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AppPageView;

class AppPagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AppPagePresenter(AppPageView& v);

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

    virtual ~AppPagePresenter() {};

private:
    AppPagePresenter();

    AppPageView& view;
};

#endif // APPPAGEPRESENTER_HPP

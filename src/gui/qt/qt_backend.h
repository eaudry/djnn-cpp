/*
 *  djnn v2
 *
 *  The copyright holders for the contents of this file are:
 *      Ecole Nationale de l'Aviation Civile, France (2018)
 *  See file "license.terms" for the rights and conditions
 *  defined by copyright holders.
 *
 *
 *  Contributors:
 *      Mathieu Magnaudet <mathieu.magnaudet@enac.fr>
 *
 */

#pragma once

#include "qt_context.h"
#include "qt_picking_view.h"
#include "../abstract_backend.h"
#include "../../core/execution/component_observer.h"
#include <QtGui/QPainterPath>

class QWidget;
class QPainter;

namespace djnn
{
  using namespace std;

  class QtContextManager;
  class QtBackend : public AbstractBackend
  {
  public:
    static QtBackend* instance ();
    virtual
    ~QtBackend ();
    void
    save_context ();
    void
    restore_context ();
    void
    set_painter (QPainter* p);
    void
    set_picking_view (QtPickingView *p);
    QPainter *painter () { return _painter; }
    WinImpl*
    create_window (Window *win, const std::string& title, double x, double y, double w, double h) override;

    //shapes
    void
    draw_rect (AbstractGShape *s, double x, double y, double w, double h, double rx, double ry) override;
    void
    draw_circle (AbstractGShape *s, double cx, double cy, double r) override;
    void
    draw_ellipse (AbstractGShape *s, double cx, double cy, double rx, double ry) override;
    void
    draw_line (AbstractGShape *s, double x1, double y1, double x2, double y2) override;
    void
    draw_text (Text *t) override;
    void
    draw_poly (Poly* p) override;
    void
    draw_poly_point (double x, double y) override;
    void
    draw_path (Path *p) override;
    void
    draw_path_move (double x, double y) override;
    void
    draw_path_line (double x, double y) override;
    void
    draw_path_quadratic (double x1, double y1, double x, double y) override;
    void
    draw_path_cubic (double x1, double y1, double x2, double y2, double x, double y) override;
    void
    draw_path_arc (double rx, double ry, double rotx, double fl, double swfl, double x, double y) override;
    void
    draw_path_closure () override;
    void
    draw_path_segment (double xc, double yc, double th0, double th1, double rx, double ry, double xAxisRotation);
    void
    draw_rect_clip (AbstractGShape *r, double x, double y, double w, double h) override;
    void
    draw_path_clip (Path *p) override;
    void
    draw_image (Image *i) override;

    //style
    void
    load_fill_color (int r, int g, int b) override;
    void
    load_outline_color (int r, int g, int b) override;
    void
    load_fill_rule (djnFillRuleType rule) override;
    void
    load_no_outline () override;
    void
    load_no_fill () override;
    void
    load_texture (const std::string &path) override;
    void
    load_outline_opacity (float alpha) override;
    void
    load_fill_opacity (float alpha) override;
    void
    load_outline_width (double w) override;
    void
    load_outline_cap_style (djnCapStyle cap) override;
    void
    load_outline_join_style (djnJoinStyle join) override;
    void
    load_outline_miter_limit (int limit) override;
    void
    load_dash_array (vector<double> dash) override;
    void
    load_no_dash_array () override;
    void
    load_dash_offset (double offset) override;
    void
    load_gradient_stop (int r, int g, int b, float a, float offset) override;
    void
    load_linear_gradient (LinearGradient *g) override;
    void
    load_radial_gradient (RadialGradient *g) override;
    void
    load_font_size (djnLengthUnit unit, double size) override;
    void
    load_font_weight (int weight) override;
    void
    load_font_style (djnFontSlope style) override;
    void
    load_font_family (const string &family) override;
    void
    load_text_anchor (djnAnchorType anchor) override;

    //transformations
    void
    load_translation (double tx, double ty) override;
    void
    load_gradient_translation (double tx, double ty) override;
    void
    load_rotation (double a, double cx, double cy) override;
    void
    load_gradient_rotation (double a, double cx, double cy) override;
    void
    load_scaling (double sx, double sy, double cx, double cy) override;
    void
    load_gradient_scaling (double sx, double sy, double cx, double cy) override;
    void
    load_skew_x (double a) override;
    void
    load_gradient_skew_x (double a) override;
    void
    load_skew_y (double a) override;
    void
    load_gradient_skew_y (double a) override;
    void
    load_homography (double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24,
		     double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44)
			 override;
    void
    load_gradient_homography (double m11, double m12, double m13, double m21, double m22, double m23, double m31,
			      double m32, double m33) override;

  private:
    static std::shared_ptr<QtBackend> _instance;
    static std::once_flag onceFlag;
    QtBackend ();
    void
    load_drawing_context (double tx, double ty, double width, double height);
    void
    load_pick_context (AbstractGShape *s);
    void
    prepare_gradient (AbstractGradient *g);
    bool
    is_in_picking_view (AbstractGShape *s);
    QPainter *_painter;
    QtPickingView *_picking_view;
    unique_ptr<QtContextManager> _context_manager;
    QPolygonF cur_poly;
    QPainterPath cur_path;
    QLinearGradient cur_linear_gradient;
    QRadialGradient cur_radial_gradient;
    QGradient* cur_gradient;
  };

} /* namespace djnn */

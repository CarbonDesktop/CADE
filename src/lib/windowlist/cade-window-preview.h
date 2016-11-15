#ifndef __CADE_WINDOW_PREVIEW_H__
#define __CADE_WINDOW_PREVIEW_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_WINDOW_PREVIEW            (cade_window_preview_get_type ())
#define CADE_WINDOW_PREVIEW(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_WINDOW_PREVIEW, CadeWindowPreview))
#define CADE_IS_WINDOW_PREVIEW(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_WINDOW_PREVIEW))
#define CADE_WINDOW_PREVIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_WINDOW_PREVIEW, CadeWindowPreviewClass))
#define CADE_IS_WINDOW_PREVIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_WINDOW_PREVIEW))
#define CADE_WINDOW_PREVIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_WINDOW_PREVIEW, CadeWindowPreviewClass))

typedef struct _CadeWindowPreview        CadeWindowPreview;
typedef struct _CadeWindowPreviewClass   CadeWindowPreviewClass;

GType              cade_window_preview_get_type (void) G_GNUC_CONST;
CadeWindowPreview *cade_window_preview_new (gint win);

G_END_DECLS

#endif /* __CADE_WINDOW_PREVIEW_H__ */

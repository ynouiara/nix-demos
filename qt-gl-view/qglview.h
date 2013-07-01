#include <QObject>
#include <QGLWidget>
#include <WebKit2/WKContext.h>
#include <WebKit2/WKPage.h>
#include <WebKit2/WKView.h>
#include <NIXEvents.h>

class QMouseEvent;
class QKeyEvent;

typedef struct {
    WKContextRef webContext;
    WKViewRef webView;
    WKPageRef webPage;
    WKViewClient webViewClient;
    WKPageLoaderClient webPageLoaderClient;
} WebKitWrapper;

class QGLView : public QGLWidget
{
    Q_OBJECT
public:
    QGLView(const QString &url, QWidget *parent = 0);

private:
    static void viewNeedsDisplay(WKViewRef view, WKRect rect, const void *clientInfo);
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    NIXMouseEvent nixMouseEvent();
    NIXKeyEvent nixKeyEvent();
    void fillNIXEventMousePos(NIXMouseEvent &nixEvent, QMouseEvent *event);
    void sendMousePressOrReleaseEvent(QMouseEvent *event);
    void sendKeyPressOrReleaseEvent(QKeyEvent *event);

    void initWebKitWrapper(const QString &url);
    WebKitWrapper *m_webKitWrapper;
};
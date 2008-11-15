#include <QPixmap>
#include <QResizeEvent>

#include "jdisplay.h"

JDisplay *JDisplay::m_instance = NULL;

JDisplay::JDisplay()
  : QStackedWidget(NULL), m_fullscreen(false), m_reversed(false), m_backbuffer(new QPixmap)
{
  setWindowTitle("phoneME");
}

JDisplay::~JDisplay()
{
}

JDisplay *JDisplay::current()
{
  if (!m_instance)
    init();
  return m_instance;
}

void JDisplay::init()
{
  if (!m_instance)
    m_instance = new JDisplay;
}

void JDisplay::destroy()
{
  if (m_instance)
  {
    delete m_instance;
    m_instance = NULL;
  }
}

QPixmap *JDisplay::backBuffer() const
{
  return m_backbuffer;
}

void JDisplay::resizeEvent(QResizeEvent *e)
{
  resizeBackBuffer(e->size().width(), e->size().height());
}

// resize backbuffer only if required size is bigger than qpixmap size to minimize amount of pixmap reallocations
void JDisplay::resizeBackBuffer(int newWidth, int newHeight)
{
  if ((m_backbuffer->isNull()) || (newWidth>m_backbuffer->width() || newHeight>m_backbuffer->height()))
  {
    QPixmap *old_buffer = m_backbuffer;
    m_backbuffer = new QPixmap(qMax(old_buffer->width(), newWidth), qMax(old_buffer->height(), newHeight));
    m_backbuffer->fill();
    delete old_buffer;
  }
}

void JDisplay::setFullScreenMode(bool mode)
{
  if (mode!=m_fullscreen) // Do we actually need to change state?
  {
    m_fullscreen = mode;
    QString title = windowTitle();
    setWindowTitle( QLatin1String("_allow_on_top_"));
    setWindowState(windowState() ^ Qt::WindowFullScreen);
    setWindowTitle(title);
  }
}

bool JDisplay::fullScreenMode() const
{
  return m_fullscreen;
}

// TODO: implement this
void JDisplay::setReversedOrientation(bool reverse)
{
}

bool JDisplay::reversedOrientation() const
{
  return m_reversed;
}

int JDisplay::displayWidth() const
{
  return m_width;
}

int JDisplay::displayHeight() const
{
  return m_height;
}

void JDisplay::setDisplayWidth(int w)
{
  m_width = w;
}

void JDisplay::setDisplayHeight(int h)
{
  m_height = h;
}

#include "moc_jdisplay.cpp"
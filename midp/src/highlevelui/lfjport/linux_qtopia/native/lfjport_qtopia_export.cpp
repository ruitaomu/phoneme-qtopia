#include <lfjport_export.h>
#include <japplication.h>
#include <jdisplay.h>
#include "lfjport_qtopia_screen.h"
#include "lfjport_qtopia_keymap.h"
#include <midp_logging.h>
#include <midp_constants_data.h>

/**
 * @file
 * Additional porting API for Java Widgets based port of abstract
 * command manager.
 */


extern "C"
  {

  /**
  * Initializes the LCDUI native resources.
  *
  * @return <tt>0</tt> upon successful initialization, or
  *         <tt>other value</tt> otherwise
  */
  int lfjport_ui_init()
  {
    JApplication::init();
    JDisplay::init();
    LFJKeyMap::init();
    LFJScreen::init();
    JDisplay::current()->addWidget(LFJScreen::instance());
    JDisplay::current()->setCurrentWidget(LFJScreen::instance());
    JApplication *app = JApplication::instance();
    app->showMainWidget(JDisplay::current());
    LFJScreen::instance()->setFocus(Qt::ActiveWindowFocusReason);
    return 0;
  }

  /**
  * Finalize the LCDUI native resources.
  */
  void lfjport_ui_finalize()
  {
    JDisplay::current()->hide();
    LFJScreen::destroy();
    LFJKeyMap::destroy();
    JDisplay::destroy();
    JApplication::destroy();
  }

  /**
  * Bridge function to request a repaint
  * of the area specified.
  *
  * @param x1 top-left x coordinate of the area to refresh
  * @param y1 top-left y coordinate of the area to refresh
  * @param x2 bottom-right x coordinate of the area to refresh
  * @param y2 bottom-right y coordinate of the area to refresh
  */
  void lfjport_refresh(int hardwareId, int x1, int y1, int x2, int y2)
  {
    (void)hardwareId;
    // qDebug("lfjport_refresh(%d, %d, %d, %d)", x1, y1, x2, y2);
    LFJScreen::instance()->repaint(x1, y1, x2-x1+1, y2-y1+1);
  }

  /**
  * Porting API function to update scroll bar.
  *
  * @param scrollPosition current scroll position
  * @param scrollProportion maximum scroll position
  * @return status of this call
  */
  int lfjport_set_vertical_scroll(
    int scrollPosition, int scrollProportion)
  {
    /* Suppress unused parameter warnings */
    (void)scrollPosition;
    (void)scrollProportion;
    //!TODO
  #warning Think about lfjport_set_vertical_scroll
    return 0;
  }

  /**
  * Turn on or off the full screen mode
  *
  * @param mode true for full screen mode
  *             false for normal
  */
  void lfjport_set_fullscreen_mode(int hardwareId, jboolean mode)
  {
    (void)hardwareId;
    JDisplay::current()->setFullScreenMode(mode);
  }

  jboolean lfjport_reverse_orientation(int hardwareId)
  {
    (void)hardwareId;
    JDisplay::current()->setReversedOrientation(!JDisplay::current()->reversedOrientation());
    return JDisplay::current()->reversedOrientation();
  }

  jboolean lfjport_get_reverse_orientation(int hardwareId)
  {
    (void)hardwareId;
    return JDisplay::current()->reversedOrientation();
  }

  int lfjport_get_screen_width(int hardwareId)
  {
    (void)hardwareId;
    return JDisplay::current()->displayWidth();
  }

  int lfjport_get_screen_height(int hardwareId)
  {
    (void)hardwareId;
    return JDisplay::current()->displayHeight();
  }

  /**
  * Bridge function to ask MainWindow object for the full screen mode
  * status.
  */
  jboolean lfjport_is_fullscreen_mode()
  {
    return JDisplay::current()->fullScreenMode();
  }

  /**
  * Resets native resources when foreground is gained by a new display.
  */
  void lfjport_gained_foreground(int hardwareId)
  {
    (void)hardwareId;
  }

  /**
  * Flushes the offscreen buffer directly to the device screen.
  * The size of the buffer flushed is defined by offscreen buffer width
  * and passed in height.
  * Offscreen_buffer must be aligned to the top-left of the screen and
  * its width must be the same as the device screen width.
  * @param graphics The Graphics handle associated with the screen.
  * @param offscreen_buffer The ImageData handle associated with
  *                         the offscreen buffer to be flushed
  * @param height The height to be flushed
  * @return KNI_TRUE if direct_flush was successful, KNI_FALSE - otherwise
  */
  jboolean lfjport_direct_flush(int hardwareID, const java_graphics *g,
                    const java_imagedata *offscreen_buffer, int h)
  {
    (void)hardwareID; (void)g; (void)offscreen_buffer; (void)h;

    return KNI_FALSE;
  }

  /**
  * Check if native softbutton is supported on platform
  *
  * @return KNI_TRUE if native softbutton is supported, KNI_FALSE - otherwise
  */
  jboolean lfjport_is_native_softbutton_layer_supported()
  {
    return KNI_TRUE;
  }

  /**
  * Request platform to draw a label in the soft button layer.
  *
  * @param label Label to draw (UTF16)
  * @param len Length of the lable (0 will cause removal of current label)
  * @param index Index of the soft button in the soft button bar.
  */
  void lfjport_set_softbutton_label_on_native_layer (unsigned short *label,
                                                  int len,
                                                  int index)
  {
    QString qstr_label = QString::fromUtf16(label, len);
    LFJScreen::instance()->setSoftButtonLabel(index, qstr_label);
  }

  /**
   * Handle clamshell event
   */
  void lfjport_handle_clamshell_event()
  {
  }

  /**
   * get currently enabled hardware display id
   */
  int lfjport_get_current_hardwareId()
  {
    return 0;
  }

  /** 
   * Get display device name by id
   */
  char * lfjport_get_display_name(int hardwareId)
  {
    (void)hardwareId;
    return NULL;
  }


  /**
   * Check if the display device is primary
   */
  jboolean lfjport_is_display_primary(int hardwareId)
  {
    (void)hardwareId;
    return KNI_TRUE;
  }

  /**
   * Check if the display device is build-in
   */
  jboolean lfjport_is_display_buildin(int hardwareId)
  {
    (void)hardwareId;
    return KNI_TRUE;
  }

  /**
   * Check if the display device supports pointer events
   */
  jboolean lfjport_is_display_pen_supported(int hardwareId)
  {
    (void)hardwareId;
    return KNI_TRUE;
  }

  /**
   * Check if the display device supports pointer motion  events
   */
  jboolean lfjport_is_display_pen_motion_supported(int hardwareId)
  {
    (void)hardwareId;
    return KNI_TRUE;
  }

  /**
   * Get display device capabilities
   */
  int lfjport_get_display_capabilities(int hardwareId)
  {
    (void)hardwareId;
    return 0xff;
  }

  static jint displays[] = {0};
  /**
   * Get the list of display device ids
   */
  jint* lfjport_get_display_device_ids(jint* n)
  {
    *n = 1;
    return displays;
  }

  /**
   * Notify the display device state has been changed
   */
  void lfjport_display_device_state_changed(int hardwareId, int state)
  {
    (void)hardwareId;
    (void)state;
  }

}

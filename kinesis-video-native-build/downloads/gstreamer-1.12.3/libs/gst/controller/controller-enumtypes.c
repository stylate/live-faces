


#include "controller-enumtypes.h"

#include "gstinterpolationcontrolsource.h" 
#include "gstlfocontrolsource.h"

/* enumerations from "gstinterpolationcontrolsource.h" */
GType
gst_interpolation_mode_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { GST_INTERPOLATION_MODE_NONE, "GST_INTERPOLATION_MODE_NONE", "none" },
      { GST_INTERPOLATION_MODE_LINEAR, "GST_INTERPOLATION_MODE_LINEAR", "linear" },
      { GST_INTERPOLATION_MODE_CUBIC, "GST_INTERPOLATION_MODE_CUBIC", "cubic" },
      { GST_INTERPOLATION_MODE_CUBIC_MONOTONIC, "GST_INTERPOLATION_MODE_CUBIC_MONOTONIC", "cubic-monotonic" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = g_enum_register_static ("GstInterpolationMode", values);
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
  return g_define_type_id__volatile;
}

/* enumerations from "gstlfocontrolsource.h" */
GType
gst_lfo_waveform_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { GST_LFO_WAVEFORM_SINE, "GST_LFO_WAVEFORM_SINE", "sine" },
      { GST_LFO_WAVEFORM_SQUARE, "GST_LFO_WAVEFORM_SQUARE", "square" },
      { GST_LFO_WAVEFORM_SAW, "GST_LFO_WAVEFORM_SAW", "saw" },
      { GST_LFO_WAVEFORM_REVERSE_SAW, "GST_LFO_WAVEFORM_REVERSE_SAW", "reverse-saw" },
      { GST_LFO_WAVEFORM_TRIANGLE, "GST_LFO_WAVEFORM_TRIANGLE", "triangle" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = g_enum_register_static ("GstLFOWaveform", values);
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
  return g_define_type_id__volatile;
}




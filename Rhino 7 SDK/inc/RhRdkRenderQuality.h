
#pragma once // SDK header

enum RDK_DEPRECATED eRhRdkRenderQuality { rcmQualNone, rcmQualLow, rcmQualMedium, rcmQualFull };
RDK_DEPRECATED bool IsRenderQualityHigher(eRhRdkRenderQuality a, eRhRdkRenderQuality b);

enum class RhRdkPreviewQuality : unsigned int
{
	None                    = 0, // No quality set.
	Low                     = 1, // Low quality rendering for quick preview.
	Medium                  = 2, // Medium quality rendering for intermediate preview.
	IntermediateProgressive = 3, // Intermediate update, always considered better quality than the previous IntermediateProgressive, but not as high as Full.
	Full                    = 4, // Full quality rendering (quality comes from user settings).
};

RHRDK_SDK bool IsPreviewQualityHigher(RhRdkPreviewQuality a, RhRdkPreviewQuality b);

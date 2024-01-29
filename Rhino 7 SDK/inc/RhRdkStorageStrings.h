
#pragma once // SDK header

#include "RhRdkContentKinds.h"

#define SLASH L"/"

// This is the structure of the RDK document XML.

#define SS_DOCUMENT                         L"render-content-manager-document"

	#define SS_EMBEDDED_FILES                   L"embedded-files"

		#define SS_FILE                             L"file"

	#define SS_CONTENT                          L"content"

	#define SS_DEFAULT_CONTENT_SECTION          L"default-content-section"

	#define SS_SETTINGS                             L"settings"

		#define SS_NAMED_VIEWS                         L"named-views"
		#define SS_NAMED_CPLANES                       L"named-cplanes"
		#define SS_NAMED_POSITIONS                     L"named-positions"
		#define SS_NAMED_SNAPSHOTS                     L"named-snapshots"
			#define SS_SORT_MODE                           L"sort-mode"
				#define SS_SORT_MODE_ASCENDING                 L"ascending"
				#define SS_SORT_MODE_DESCENDING                L"descending"
				#define SS_SORT_MODE_CUSTOM                    L"custom"

		#define SS_MISCELLANEOUS                       L"miscellaneous"

			#define SS_CUSTOM_IMAGE_SIZE_IS_PRESET        L"custom-image-size-is-preset"

			#define SS_NAME_COLLISION_PREFIX              L"smart-merge-name-collision-prefix" // Obsolete

			#define SS_NAME_COLLISION_SUPPRESS            L"smart-merge-name-collision-suppress"
				#define SS_IMPORT                           L"import"
				#define SS_PASTE                            L"paste"

		#define SS_EXCLUDED_RENDER_ENGINES            L"excluded-render-engines"

			#define SS_UUIDS                            L"uuids"

		#define SS_FILTERS                            L"filters"

			#define SS_NAME_FILTER                      L"name-filter"
			#define SS_NAME_FILTER_INVERT               L"name-filter-invert"
			#define SS_SHOW_UNASSIGNED                  L"show-unassigned-materials"
			#define SS_SHOW_V4                          L"show-v4-materials"
			#define SS_SHOW_HIDDEN                      L"show-hidden-materials"
			#define SS_SHOW_REFERENCE                   L"show-reference-materials"

		#define SS_RENDERING                          L"rendering"

			#define SS_RENDER_CHANNELS                L"render-channels"

				#define SS_RCH_MODE                     L"mode"
				//----- +++++++++++++
				#define SS_RCH_MODE_AUTOMATIC             L"automatic"
				#define SS_RCH_MODE_CUSTOM                L"custom"

				#define SS_RCH_LIST                     L"list"

			#define SS_EMBED_SUPPORT_FILES_ON           L"embed-support-files-on"
			#define SS_INCLUDE_TEX_MAT_ON               L"include-texmat-on"
			#define SS_GAMMA                            L"gamma"
			#define SS_USE_DITHERING                    L"use-dithering"
			#define SS_USE_POST_PROCESS_GAMMA           L"use-post-process-gamma"
			#define SS_USE_LINEAR_WORKFLOW              L"use-linear-workflow"

			#define SS_CUSTOM_REFLECTIVE_ENVIRONMENT_ON	L"custom-env-for-refl-and-refr-on"
			#define SS_CUSTOM_REFLECTIVE_ENVIRONMENT    L"custom-env-for-refl-and-refr"

			// Early post effects.
			#define SS_PEP_GLARE                        L"glare"
			#define SS_PEP_GLARE_GAIN                     L"gain"
			#define SS_PEP_GLARE_WHITE_POINT_BOUND        L"white-point-bound"
			#define SS_PEP_GLARE_AREA_MULTIPLIER          L"area-multiplier"
			#define SS_PEP_GLARE_SAMPLES                  L"samples"
			#define SS_PEP_GLARE_USE_LOG_SCALE            L"use-log-scale"

			#define SS_PEP_BLOOM                        L"bloom"
			#define SS_PEP_BLOOM_BRIGHTNESS_THRESHOLD     L"brightness-threshold"
			#define SS_PEP_BLOOM_RADIUS                   L"radius"
			#define SS_PEP_BLOOM_INTENSITY                L"intensity"

			#define SS_PEP_GLOW                         L"glow"
			#define SS_PEP_GLOW_GAIN                      L"gain"
			#define SS_PEP_GLOW_SENSITIVITY               L"sensitivity"
			#define SS_PEP_GLOW_AREA_VALUE                L"area-value"
			#define SS_PEP_GLOW_ITEM_NUMOF                L"num-colors"
			#define SS_PEP_GLOW_ITEM_FORMAT               L"-%u"
			#define SS_PEP_GLOW_ITEM_COLOR                L"color"
			#define SS_PEP_GLOW_ITEM_ENABLED              L"enabled"
			#define SS_PEP_GLOW_ITEM_SENSITIVITY          L"sensitivity"

			#define SS_PEP_FOG                          L"fog"
			#define SS_PEP_FOG_LEFT                       L"left"
			#define SS_PEP_FOG_TOP                        L"top"
			#define SS_PEP_FOG_RIGHT                      L"right"
			#define SS_PEP_FOG_BOTTOM                     L"bottom"
			#define SS_PEP_FOG_START_DISTANCE             L"start-distance"
			#define SS_PEP_FOG_END_DISTANCE               L"end-distance"
			#define SS_PEP_FOG_STRENGTH                   L"strength"
			#define SS_PEP_FOG_FEATHERING                 L"feathering"
			#define SS_PEP_FOG_NOISE                      L"noise"
			#define SS_PEP_FOG_BACKGROUND                 L"background"
			#define SS_PEP_FOG_COLOR                      L"color"

			#define SS_PEP_DOF                          L"depth-of-field"
			#define SS_PEP_DOF_BLUR_BACKGROUND            L"blur-background"
			#define SS_PEP_DOF_BLUR_FOCAL_DISTANCE        L"focal-distance"
			#define SS_PEP_DOF_BLUR_BLUR_AMOUNT           L"blur-amount"
			#define SS_PEP_DOF_BLUR_MAX_BLURRING          L"max-blurring"

			#define SS_PEP_DITHERING                    L"dithering"

			/**-------------------- Old tone mapping strings ------------------------------------------*/
			/*                                                                                         */
			/*  These are all deprecated. Tone mapping is now a post effect.                           */
			/*                                                                                         */
			/**/ #define SS_TONE_MAPPING                       L"tone-mapping"                       /**/
			/**/ #define SS_TONE_MAPPING_NONE                  L"none"                               /**/
			/**/ #define SS_TONE_MAPPING_BLACK_WHITE_POINT     L"black-white-point"                  /**/
			/**/ #define SS_TONE_MAPPING_LOGARITHMIC           L"logarithmic"                        /**/
			/**/ #define SS_TONE_MAPPING_FILMIC                L"filmic"                             /**/
			/**/ #define SS_TONE_MAPPING_REINHARD_2001         L"reinhard-2001"                      /**/
			/**/ #define SS_TONE_MAPPING_REINHARD_2005         L"reinhard-2005"                      /**/
			/*                                                                                         */
			/**----------------------------------------------------------------------------------------*/

			/*DEPRECATED*/ #define SS_TONE_MAPPING_METHOD L"tone-mapping-method"

			// Tone mapping post effects.
			#define SS_TONEMAP_BLACK_POINT                L"tm-black-point"
			#define SS_TONEMAP_WHITE_POINT                L"tm-white-point"

			#define SS_TONEMAP_LOG_EXPOSURE               L"exposure"
			#define SS_TONEMAP_LOG_BIAS                   L"bias"
			#define SS_TONEMAP_LOG_CONTRAST               L"contrast"

			#define SS_TONEMAP_FILMIC_PRESET              L"preset"
			#define SS_TONEMAP_FILMIC_PRESET_LOW_CONTRAST    L"low-contrast"
			#define SS_TONEMAP_FILMIC_PRESET_MEDIUM_CONTRAST L"medium-contrast"
			#define SS_TONEMAP_FILMIC_PRESET_HIGH_CONTRAST   L"high-contrast"

			#define SS_TONEMAP_FILMIC_CONTRAST               L"contrast"
			#define SS_TONEMAP_FILMIC_SATURATION             L"saturation"
			#define SS_TONEMAP_FILMIC_EXPOSURE_BIAS          L"exposure-bias"
			#define SS_TONEMAP_FILMIC_SHADOW_OFFSET          L"shadow-offset"
			#define SS_TONEMAP_FILMIC_MIDTONE_OFFSET         L"midtone-offset"
			#define SS_TONEMAP_FILMIC_HIGHLIGHT_OFFSET       L"highlight-offset"

			// Late post effects.
			#define SS_PEP_GAMMA                          L"gamma"

			#define SS_DITHERING                          L"dithering"
			//----- ++++++++++++
			#define SS_DITHERING_NONE                       L"none" // OBSOLETE
			#define SS_DITHERING_FLOYD_STEINBERG            L"floyd-steinberg"
			#define SS_DITHERING_SIMPLE_NOISE               L"simple-noise"

			// Watermark.
			#define SS_PEP_WATERMARK                        L"watermark"
			#define SS_PEP_WATERMARK_FONT_FACE              L"font-face"
			#define SS_PEP_WATERMARK_FONT_COLOR             L"font-color"
			#define SS_PEP_WATERMARK_FONT_POINTS            L"font-points"
			#define SS_PEP_WATERMARK_TRANSPARENCY           L"transparency"

			// Hue/Sat/Lum.
			#define SS_PEP_HUESATLUM                        L"hue-sat-lum"
			#define SS_PEP_HUESATLUM_HUE                    L"hue"
			#define SS_PEP_HUESATLUM_SAT                    L"saturation"
			#define SS_PEP_HUESATLUM_LUM                    L"luminance"

			// Bri/Con.
			#define SS_PEP_BRICON                           L"bri-con"
			#define SS_PEP_BRICON_BRI                       L"brightness"
			#define SS_PEP_BRICON_CON                       L"contrast"

			// Multiplier
			#define SS_PEP_MULTIPLIER                       L"multiplier"
			#define SS_PEP_MULTIPLIER_VALUE                 L"multiplier-value"

			// Noise
			#define SS_PEP_NOISE                            L"noise"
			#define SS_PEP_NOISE_AMOUNT                     L"noise-amount"
			#define SS_PEP_NOISE_MONOCHROME                 L"noise-monochrome"

			// Gaussian blur
			#define SS_PEP_GAUSSIAN_BLUR                    L"gaussian-blur"
			#define SS_PEP_GAUSSIAN_BLUR_HORZ               L"gaussian-blur-horz"
			#define SS_PEP_GAUSSIAN_BLUR_VERT               L"gaussian-blur-vert"
			#define SS_PEP_GAUSSIAN_BLUR_AMOUNT             L"gaussian-blur-amount"

			// If you add more, remember to update the CRhRdkDocument SDK comments and validation.

			#define SS_TONE_MAPPER_PARAMS                  L"tone-mapper-params"

		#define SS_SUN                                    L"sun"

			#define SS_SUN_ENABLE_ALLOWED                   L"enable-allowed"
			#define SS_SUN_ENABLE_ON                        L"enable-on"
			#define SS_SUN_MANUAL_CONTROL_ALLOWED           L"manual-control-allowed"
			#define SS_SUN_MANUAL_CONTROL_ON                L"manual-control-on"
			#define SS_SUN_NORTH                            L"north"
			#define SS_SUN_AZIMUTH                          L"sun-azimuth"
			#define SS_SUN_ALTITUDE                         L"sun-altitude"
			#define SS_SUN_DATE_YEAR                        L"year"
			#define SS_SUN_DATE_MONTH                       L"month"
			#define SS_SUN_DATE_DAY                         L"day"
			#define SS_SUN_TIME_HOURS                       L"time"
			#define SS_SUN_DAYLIGHT_SAVING_ON               L"daylight-saving-on"
			#define SS_SUN_DAYLIGHT_SAVING_MINUTES          L"daylight-saving-minutes"
			#define SS_SUN_OBSERVER_LATITUDE                L"observer-latitude"
			#define SS_SUN_OBSERVER_LONGITUDE               L"observer-longitude"
			#define SS_SUN_OBSERVER_TIMEZONE                L"observer-timezone"

			// Additions for V5.
			#define SS_SUN_SKYLIGHT_ON                      L"skylight-on"
			#define SS_SUN_SKYLIGHT_SHADOW_INTENSITY        L"skylight-shadow-intensity"
			#define SS_SUN_SKYLIGHT_CUSTOM_ENVIRONMENT_ON   L"skylight-custom-environment-on"
			#define SS_SUN_SKYLIGHT_CUSTOM_ENVIRONMENT      L"skylight-custom-environment"

			// Additions for V6
			#define SS_SUN_SHADOW_INTENSITY                 L"shadow-intensity"

			// Additions for V7
			#define SS_SUN_INTENSITY                        L"intensity"

		#define SS_SAFE_FRAME                       L"safe-frame"

			#define SS_SF_ON                            L"on"
			#define SS_SF_PERSPECTIVE_ONLY              L"perspective-only"
			#define SS_SF_FIELD_DISPLAY_ON              L"field-display-on"
			#define SS_SF_LIVE_FRAME                    L"live-frame"
			#define SS_SF_ACTION_FRAME                  L"action-frame"
			#define SS_SF_TITLE_FRAME                   L"title-frame"
				#define SS_SFF_ON                           L"on"
				#define SS_SFF_XSCALE                       L"x-scale"
				#define SS_SFF_YSCALE                       L"y-scale"
				#define SS_SFF_LINK                         L"link"

		#define SS_GROUND_PLANE                     L"ground-plane"

			#define SS_GP_ON                            L"on"
			#define SS_GP_ALTITUDE                      L"altitude"
			#define SS_GP_MATERIAL                      L"material"
			#define SS_GP_TEXTURE_OFFSET                L"texture-offset"
			#define SS_GP_TEXTURE_SIZE                  L"texture-size"
			#define SS_GP_TEXTURE_ROTATION              L"texture-rotation"
			#define SS_GP_OFFSET_LOCK                   L"offset-lock"
			#define SS_GP_REPEAT_LOCK                   L"repeat-lock"
			#define SS_GP_SHOW_UNDERSIDE                L"show-underside"
			#define SS_GP_AUTO_ALTITUDE                 L"auto-altitude"
			#define SS_GP_SHADOW_ONLY                   L"shadow-only"

		#define SS_POST_EFFECTS                     L"post-effects" // OBSOLETE
			#define SS_PE_PLUG_INS                      L"plug-ins" // OBSOLETE

		#define SS_POST_EFFECTS_NEW                 L"post-effects-new"

			#define SS_APPLY_TONE_MAPPING_WHILE_RENDERING L"apply-tone-mapping-while-rendering" // OBSOLETE

			#define SS_PEP_TYPE_EARLY            L"early"
			#define SS_PEP_TYPE_TONE             L"tone-mapping"
			#define SS_PEP_TYPE_LATE             L"late"

			#define SS_PEP_SELECTION                    L"selection"

			#define SS_PEP_SELECTION_POSTFIX            L"-" SS_PEP_SELECTION

			#define SS_PEP_EARLY_SELECTION              SS_PEP_TYPE_EARLY SS_PEP_SELECTION_POSTFIX
			#define SS_PEP_TONE_SELECTION               SS_PEP_TYPE_TONE  SS_PEP_SELECTION_POSTFIX
			#define SS_PEP_LATE_SELECTION               SS_PEP_TYPE_LATE  SS_PEP_SELECTION_POSTFIX

					#define SS_PEP_PLUG_IN                      L"plug-in"
					#define SS_PEP_NAME                         L"name"
					#define SS_PEP_ID                           L"id"
					#define SS_PEP_SHOWN                        L"shown"
					#define SS_PEP_ON                           L"on"
					#define SS_PEP_STATE                        L"state"

		#define SS_CUSTOM_RENDER_MESH               L"custom-render-mesh"

			#define SS_PROVIDERS                        L"providers"

				#define SS_PROVIDER                         L"provider"

					#define SS_PROVIDER_ID                      L"id"
					#define SS_PROVIDER_ON                      L"on"

	#define SS_PREVIEW_SECTION                      L"preview-section"

		#define SS_ITEM                             L"item"

			#define SS_CONTENT_ID                       L"content-id"
			#define SS_SCENE_SCALE                      L"scene-scale"
			#define SS_ANGLE_X                          L"angle-x"
			#define SS_ANGLE_Y                          L"angle-y"
			#define SS_GEOMETRY                         L"geometry"
			#define SS_BACKGROUND                       L"background"
			#define SS_LIGHTING                         L"lighting"
			#define SS_ENVIRONMENT_UUID                 L"environment-uuid"

			#define SS_ROTATION_TYPE                    L"rotation-type"
				#define SS_RT_OBJECT                        L"object"
				#define SS_RT_CAMERA                        L"camera"

	#define SS_POSTFIX_SECTION                      L"-section"

			#define SS_PARAMETERS                           L"parameters"
			#define SS_SIMULATION                           L"simulation"
			#define SS_PREVIEW                              L"preview"
			#define SS_CUSTOM_DATA                          L"custom-data"
			#define SS_TYPE_NAME                            L"type-name"
			#define SS_TYPE_ID                              L"type-id"
			#define SS_INSTANCE_ID                          L"instance-id"
			#define SS_RENDER_ENGINE_ID                     L"render-engine-id"
			#define SS_PLUG_IN_ID                           L"plug-in-id"
			#define SS_GROUP_ID                             L"group-id"
			#define SS_INSTANCE_NAME                        L"instance-name"
			#define SS_CHILD_SLOT_NAME                      L"child-slot-name"
			#define SS_NOTES                                L"notes"
			#define SS_TAGS                                 L"tags"
			#define SS_HIDDEN                               L"hidden"
			#define SS_REFERENCE                            L"reference"
			#define SS_REFERENCE_MARKER                     L"reference-marker" // For passing ImportReferenceMode flag from loading to content creation.
			#define SS_AUTO_DELETE                          L"auto-delete"

			#define SS_ENV_BACKGROUND_COLOR         L"background-color"

#define SS_UD_ROOT                              L"render-content-manager-data"

	#define SS_UD_MATERIAL                          L"material"

		#define SS_UD_NAME                              L"name"
		#define SS_UD_INSTANCE_ID                       L"instance-id"

/*	#define SS_UD_ADVANCED_TEXTURE_PREVIEW          L"advanced-texture-preview"

		#define SS_UD_ON                                L"on"

	#define SS_UD_TEXTURE_MAPPING                   L"texture-mapping"

		#define SS_UD_CHANNEL                           L"channel"

			#define SS_UD_CHANNEL_ID                        L"channel-id"
			#define SS_UD_MAPPING_ID                        L"mapping-id"
			#define SS_UD_LOCAL_MATRIX                      L"local-matrix"*/

	#define SS_UD_DECALS                            L"decals"

		#define SS_UD_DECAL                             L"decal"

			#define SS_UD_DECAL_CUSTOM                      L"custom"
			#define SS_UD_DECAL_CUSTOM_RENDERER             L"renderer"
			#define SS_UD_DECAL_CUSTOM_PARAMS                   L"parameters"

			#define SS_UD_DECAL_INSTANCE_ID                 L"instance-id"

			#define SS_UD_DECAL_MAPPING                     L"mapping"
			//----- +++++++++++++++++++
			#define SS_UD_DECAL_MAPPING_PLANAR              L"planar"
			#define SS_UD_DECAL_MAPPING_CYLINDRICAL         L"cylindrical"
			#define SS_UD_DECAL_MAPPING_SPHERICAL           L"spherical"
			#define SS_UD_DECAL_MAPPING_UV                  L"uv"
			#define SS_UD_DECAL_MAPPING_NONE                L"none"

			#define SS_UD_DECAL_PROJECTION                  L"projection"
			//----- ++++++++++++++++++++++
			#define SS_UD_DECAL_PROJECTION_FORWARD          L"forward"
			#define SS_UD_DECAL_PROJECTION_BACKWARD         L"backward"
			#define SS_UD_DECAL_PROJECTION_BOTH             L"both"
			#define SS_UD_DECAL_PROJECTION_NONE             L"none"

			#define SS_UD_DECAL_MAP_TO_INSIDE_ON            L"map-to-inside-on"
			#define SS_UD_DECAL_TRANSPARENCY                L"transparency"
			#define SS_UD_DECAL_TEXTURE_INSTANCE            L"texture-instance"

			#define SS_UD_DECAL_HEIGHT                      L"height"
			#define SS_UD_DECAL_ORIGIN                      L"origin"
			#define SS_UD_DECAL_RADIUS                      L"radius"
			#define SS_UD_DECAL_HORZ_SWEEP_STA              L"latitude-start"  // These are badly named
			#define SS_UD_DECAL_HORZ_SWEEP_END              L"latitude-stop"   // but I'm not going to
			#define SS_UD_DECAL_VERT_SWEEP_STA              L"longitude-start" // change them because
			#define SS_UD_DECAL_VERT_SWEEP_END              L"longitude-stop"  // of old documents.
			#define SS_UD_DECAL_VECTOR_UP                   L"vector-up"
			#define SS_UD_DECAL_VECTOR_ACROSS               L"vector-across"
			#define SS_UD_DECAL_MIN_U                       L"min-u"
			#define SS_UD_DECAL_MIN_V                       L"min-v"
			#define SS_UD_DECAL_MAX_U                       L"max-u"
			#define SS_UD_DECAL_MAX_V                       L"max-v"

			#define SS_UD_DECAL_IS_TEMPORARY                L"is-temporary"

// Content meta-data
#define SS_CONTENT_META_DATA                    L"meta-data"
	#define SS_CONTENT_META_DATA_RENDERER_NAME    L"renderer-name"
	#define SS_CONTENT_META_DATA_TYPE_NAME        L"type-name"

// Texture simulation.
#define RDK_TEX_SIM_FILENAME         L"filename"
#define RDK_TEX_SIM_REPEAT           L"repeat"
#define RDK_TEX_SIM_OFFSET           L"offset"
#define RDK_TEX_SIM_ROTATION         L"rotation"
#define RDK_TEX_SIM_WRAP_TYPE        L"wrap-type"
#define RDK_TEX_SIM_MAPPING_CHANNEL  L"mapping-channel"
#define RDK_TEX_SIM_PROJECTION_MODE  L"projection-mode"

// Miscellaneous.
#define SS_HDR_INTENSITY         L"intensity" // This is an alias for FS_TEX_HDR_MULTIPLIER.
#define SS_MAX_SIMULATED_HEIGHT  L"max-simulated-height"

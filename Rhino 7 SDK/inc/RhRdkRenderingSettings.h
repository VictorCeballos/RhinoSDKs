
#pragma once

#include "RhRdkDefinitions.h"

// This class is deprecated. Please call the equivalent methods in CRhRdkDocument.

class RDK_DEPRECATED_CLASS RHRDK_SDK CRhRdkRenderingSettings
{
public:
	CRhRdkRenderingSettings(const CRhinoDoc* =nullptr) { }
	CRhRdkRenderingSettings(const CRhinoDoc&) { }
	CRhRdkRenderingSettings(CRhRdkDocument&) { }
	virtual ~CRhRdkRenderingSettings() { }

	bool EmbedOn(void) const;
	void SetEmbedOn(bool b);
	bool UseCustomEnvironmentForReflectionAndRefraction(void) const;
	void SetUseCustomEnvironmentForReflectionAndRefraction(bool b);
	UUID CustomEnvironmentForReflectionAndRefraction(void) const;
	void SetCustomEnvironmentForReflectionAndRefraction(const UUID& uuidInstance);
	double Gamma(void) const;
	void SetGamma(double d);
	bool UseLinearWorkflow(void) const;
	void SetUseLinearWorkflow(bool b);
	ON_wString Dithering(void) const;
	void SetDithering(const wchar_t* wsz);
	ON_wString ToneMapping(void) const;
	void SetToneMapping(const wchar_t* wsz);
	void GetToneMapperParams(class CRhRdk_XMLSection& section) const;
	void SetToneMapperParams(const class CRhRdk_XMLSection& section);
	bool ApplyToneMappingWhileRendering(void) const;
	void SetApplyToneMappingWhileRendering(bool b);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*);
};


#pragma once // UI SDK header.

// ##########################################################################################################
// ######
// ###### Important note for plug-in developers:
// ######
// ###### This file was included in the PUBLIC SDK by mistake. 3rd-party plug-ins should not use this
// ###### as it is obsolete and has been replaced by post-effect plug-ins.
// ######
// ###### It has only been kept included to avoid breaking the SDK.
// ######
// ##########################################################################################################

class CRhRdkProgress;
class CRhRdkHighDynamicRangeImage_RGB;

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkToneMapper
{
public:
	virtual ~CRhRdkToneMapper() { }

	virtual void GetParametersFromSection(const IRhRdk_XMLSection& section) = 0;
	virtual void SetParametersToSection(IRhRdk_XMLSection& section) const = 0;
	virtual ON_wString GetFriendlyParamName(const wchar_t* wszParamName, bool bEnglish) const = 0;
};

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkToneMapper_PixelBased : public CRhRdkToneMapper
{
public:
	virtual void ProcessPixel(float& r, float& g, float& b) = 0;
};

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkToneMapper_ImageBased : public CRhRdkToneMapper
{
public:
	virtual void ProcessImage(CRhRdkHighDynamicRangeImage_RGB& image, CRhRdkProgress* pProgress) = 0;
};

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkToneMapper_BlackWhitePoint : public CRhRdkToneMapper_PixelBased
{
public:
	CRhRdkToneMapper_BlackWhitePoint(float fBlackPoint=0.0f, float fWhitePoint=1.0f);
	virtual ~CRhRdkToneMapper_BlackWhitePoint();

	float BlackPoint(void) const;
	void SetBlackPoint(float);

	float WhitePoint(void) const;
	void SetWhitePoint(float);

	virtual void GetParametersFromSection(const IRhRdk_XMLSection& section);
	virtual void SetParametersToSection(IRhRdk_XMLSection& section) const;
	virtual ON_wString GetFriendlyParamName(const wchar_t* wszParamName, bool bEnglish) const;
	virtual void ProcessPixel(float& r, float& g, float& b);

protected:
	void UpdateReciprocal(void);

private:
	class CImpl;
	CImpl* m_pImpl;
};

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkToneMapper_Logarithmic : public CRhRdkToneMapper_ImageBased
{
public:
	CRhRdkToneMapper_Logarithmic(float e=1.0f, float b=0.85f, float c=1.0f);
	virtual ~CRhRdkToneMapper_Logarithmic();

	float Exposure(void) const;
	void SetExposure(float f);

	float Bias(void) const;
	void SetBias(float f);

	float Contrast(void) const;
	void SetContrast(float f);

	virtual void GetParametersFromSection(const IRhRdk_XMLSection& section);
	virtual void SetParametersToSection(IRhRdk_XMLSection& section) const;
	virtual void ProcessImage(CRhRdkHighDynamicRangeImage_RGB& image, CRhRdkProgress* pProgress);
	virtual ON_wString GetFriendlyParamName(const wchar_t* wszParamName, bool bEnglish) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

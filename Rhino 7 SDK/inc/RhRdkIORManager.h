
#pragma once

// ##########################################################################################################
// ######
// ###### Important note for plug-in developers:
// ######
// ###### This file was included in the PUBLIC SDK by mistake. 3rd-party plug-ins should not use this.
// ######
// ###### It has only been kept included to avoid breaking the SDK.
// ######
// ##########################################################################################################

/** \class CRhRdkIORManager

	This is a stack object that you can use to implement a
	menu containing IORs for various materials.

*/
class RHRDK_UI_SDK CRhRdkIORManager final
{
public:
	CRhRdkIORManager();
	CRhRdkIORManager(const wchar_t* wszFilename);
	~CRhRdkIORManager();

	void BuildMenu(class IRhRdkMenu& menu);

	bool GetIORForCmd(unsigned short cmd, double& dIOROut, ON_wString* pStringOut=nullptr) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

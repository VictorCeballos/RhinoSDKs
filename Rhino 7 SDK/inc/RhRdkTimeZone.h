
#pragma once // UI SDK header

// ##########################################################################################################
// ######
// ###### Important note for plug-in developers:
// ######
// ###### This file was included in the PUBLIC SDK by mistake. 3rd-party plug-ins should not use this.
// ######
// ###### It has only been kept included to avoid breaking the SDK.
// ######
// ##########################################################################################################

class RHRDK_UI_SDK CRhRdkTimeZone final
{
public:
	CRhRdkTimeZone();
	CRhRdkTimeZone(double lon, double lat, double dHours, const wchar_t* wszName);
	~CRhRdkTimeZone();

	/** \return the name of the time zone. */
	ON_wString Name(void) const;

	/** \return the time zone hours offset from UTC. */
	double Hours(void) const;

	/** \return the latitude of a major city in the time zone. */
	double Latitude(void) const;

	/** \return the longitude of a major city in the time zone. */
	double Longitude(void) const;

	static int Count(void);
	static const CRhRdkTimeZone* GetAt(int i);
	static void GetList(ON_ClassArray<CRhRdkTimeZone>& aOut);

private:
	class CImpl;
	CImpl* m_pImpl;
};

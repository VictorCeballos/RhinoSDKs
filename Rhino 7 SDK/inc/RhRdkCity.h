
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

class RHRDK_UI_SDK CRhRdkCity final
{
public:
	CRhRdkCity();
	CRhRdkCity(const CRhRdkCity& c);
	CRhRdkCity(double lon, double lat, double timeZoneHours, const wchar_t* wszName);
	~CRhRdkCity();

	const CRhRdkCity& operator = (const CRhRdkCity& c);

	/** \return The localized name of the city. */
	ON_wString Name(void)  const;

	/** \return The latitude of the city. */
	double Latitude(void)  const;

	/** \return The longitude of the city. */
	double Longitude(void) const;

	/** \return The time zone of the city in decimal hours. */
	double TimeZone(void)  const;

	/** \return \e true if the city has the same position as another city. */
	bool Matches(const CRhRdkCity& c) const;

	/** \return The number of cities in the city list. */
	static int Count(void);

	/** \return A city in the city list by index. */
	static const CRhRdkCity* GetAt(int i);

	/** \return All the cities in the city list. */
	static void GetList(OUT ON_SimpleArray<const CRhRdkCity*>& a);

	/** \return The nearest city to a position on Earth. */
	static const CRhRdkCity& FindNearest(double dLatitude, double dLongitude);

private:
	class CImpl;
	CImpl* m_pImpl;
};

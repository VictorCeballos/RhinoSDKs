
#pragma once // Public SDK header

/** This enum is deprecated in favor of the one below. */
enum RDK_DEPRECATED eRdkDitheringMethod { dm_none, dm_floyd_steinberg, dm_simple_noise };

/** \class IRhRdkDithering

	This interface is deprecated and only kept for backward compatibility.

*/
/*RDK_DEPRECATED*/ class RHRDK_SDK IRhRdkDithering
{
public:
	/** Call this method to get a non-const object upon which you can call non-const methods.
		Calls to this method are counted; you must call EndChange() once for every call to
		BeginChange(). Please do not use const_cast or any other means of circumventing this requirement. */
	virtual IRhRdkDithering& BeginChange(RhRdkChangeContext cc) const = 0;
	virtual bool EndChange(void) = 0;

#pragma region RH_C_SHARED_ENUM [IRhRdkDithering::Methods] [Rhino.Render.Dithering.Methods] [nested]
	/// <summary>
	/// Dithering algorithm.
	/// </summary>
	enum class Methods : unsigned int
	{
		/// <summary>No dithering</summary>
		None, // OBSOLETE - not used except in old files.
		/// <summary>Floyd Steinberg algorithm</summary>
		FloydSteinberg,
		/// <summary>Simple random noise</summary>
		SimpleNoise,
	};
#pragma endregion

	/** Get the dithering method */
	virtual Methods Method(void) const = 0;

	/** Set the dithering method */
	virtual void SetMethod(Methods m) = 0;

	/** \return \e true if this object is equal to another one. */
	virtual bool IsEqual(const IRhRdkDithering& dit) const = 0;

	/** Copy another dithering object to this one. */
	virtual void CopyFrom(const IRhRdkDithering& dit) = 0;

	/** Emergency virtual function for future expansion. Currently implemented wszFunc:
		"On"    (pvData = null; returns pointer to bool).
		"SetOn" (pvData is pointer to bool). */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

	bool On(void) const;  // [SDK_UNFREEZE]
	void SetOn(bool bOn); // [SDK_UNFREEZE]

	static IRhRdkDithering* New(void);

	virtual ~IRhRdkDithering() { }
};

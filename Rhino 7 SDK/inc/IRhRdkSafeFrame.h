
#pragma once // SDK header

class RHRDK_SDK IRhRdkSafeFrame
{
public:
	/** Call this method to get a non-const object upon which you can call non-const methods.
		Calls to this method are counted; you must call EndChange() once for every call to
		BeginChange(). Please do not use const_cast or any other means of circumventing this requirement. */
	virtual IRhRdkSafeFrame& BeginChange(RhRdkChangeContext cc) const = 0;
	virtual bool EndChange(void) = 0;

	virtual bool On(void) const = 0;
	virtual bool PerspectiveOnly(void) const = 0;
	virtual bool FieldsOn(void) const = 0;
	virtual bool LiveFrameOn(void) const = 0;
	virtual bool ActionFrameOn(void) const = 0;
	virtual bool ActionFrameLinked(void) const = 0;
	virtual double ActionFrameXScale(void) const = 0;
	virtual double ActionFrameYScale(void) const = 0;
	virtual bool TitleFrameOn(void) const = 0;
	virtual bool TitleFrameLinked(void) const = 0;
	virtual double TitleFrameXScale(void) const = 0;
	virtual double TitleFrameYScale(void) const = 0;
	virtual void SetOn(bool b) = 0;
	virtual void SetPerspectiveOnly(bool b) = 0;
	virtual void SetFieldsOn(bool b) = 0;
	virtual void SetLiveFrameOn(bool b) = 0;
	virtual void SetActionFrameOn(bool b) = 0;
	virtual void SetActionFrameLinked(bool b) = 0;
	virtual void SetActionFrameXScale(double d) = 0;
	virtual void SetActionFrameYScale(double d) = 0;
	virtual void SetTitleFrameOn(bool b) = 0;
	virtual void SetTitleFrameLinked(bool b) = 0;
	virtual void SetTitleFrameXScale(double d) = 0;
	virtual void SetTitleFrameYScale(double d) = 0;
	virtual void BeginNotifyBracket(void) = 0;
	virtual void EndNotifyBracket(void) = 0;
	virtual bool IsEqual(const IRhRdkSafeFrame& sf) const = 0;
	virtual void CopyFrom(const IRhRdkSafeFrame& sf) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;

protected:
	virtual ~IRhRdkSafeFrame() { }
};

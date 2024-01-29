
#pragma once // SDK header

#include "RhRdkContentFactory.h"

class RHRDK_SDK CRhRdkTextureFactory : public CRhRdkContentFactory
{
public:
	CRhRdkTextureFactory();
	virtual ~CRhRdkTextureFactory();

	virtual CRhRdkContent::Kinds Kind(void) const;
	virtual CRhRdkContent* NewContent(void) const;

protected:
	virtual class CRhRdkTexture* NewTexture(void) const = 0;
};

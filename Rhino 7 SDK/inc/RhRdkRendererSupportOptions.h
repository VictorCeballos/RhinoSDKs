
#pragma once // SDK header.

#include "RhRdkDefinitions.h"

enum class RhRdkSmartMergeChoice : unsigned int
{
	DiscardIncoming,    // Keep the existing content and discard the incoming content.
	AutoRenameIncoming, // Automatically rename the incoming content with [imported] post-fix and keep both.
	ReplaceExisting,    // Replace the existing content with the incoming one.
	UseDialogToAsk,     // Ask the user what to do by displaying a dialog.
};

class RHRDK_SDK CRhRdkRendererSupportOptions
{
public:
	CRhRdkRendererSupportOptions();
	virtual ~CRhRdkRendererSupportOptions();

	void PopulateAdvancedOptions(void) const;

	virtual bool AlwaysShowSunPreview(void) const;
	virtual void SetAlwaysShowSunPreview(bool b);

	virtual bool PreviewCustomRenderMeshes(void) const;
	virtual void SetPreviewCustomRenderMeshes(bool b);

	virtual bool MultithreadedTextureEvaluation(void) const;
	virtual void SetMultithreadedTextureEvaluation(bool b);

	virtual bool HarvestContentParameters(void) const;
	virtual void SetHarvestContentParameters(bool b);

	enum { size1 = 128, size2 = 256, size3 = 512, size4 = 1024, size5 = 2048 };
	virtual int  TextureSize(void) const;

	RDK_DEPRECATED virtual void SetTextureSize(int size, bool bSendEvent=true);

	virtual bool CombineEditors(void) const;
	virtual void SetCombineEditors(bool b);

	// Libraries - expanded in May 2011
	virtual bool UseDefaultLibraryPath(void) const;
	virtual void SetUseDefaultLibraryPath(bool bUseDefault);

	virtual ON_wString CustomLibraryPath(void) const;
	virtual void SetCustomLibraryPath(const wchar_t* wszPath);

	virtual bool ShowRenderContent(void) const;
	virtual bool ShowDocuments(void) const;
	virtual bool ShowCustom(void) const;

	virtual void SetShowRenderContent(bool b);
	virtual void SetShowDocuments(bool b);
	virtual void SetShowCustom(bool b);

	virtual ON_wString CustomPaths(void) const; // Semicolon delimited.
	virtual void SetCustomPaths(const wchar_t* wszPath);

	enum eInitialLocation
	{
		render_content,
		last_opened_folder,
		custom_folder
	};

	virtual eInitialLocation LibrariesInitialLocation(void) const;
	virtual void SetLibrariesInitialLocation(eInitialLocation l);

	virtual ON_wString LibrariesInitialLocationCustomFolder(void) const;
	virtual void SetLibrariesInitialLocationCustomFolder(const wchar_t* wszPath);

	//Internal use only
#if defined RHINO_SDK_MFC && defined ON_RUNTIME_WIN
	void SetLastNavigatedLocation(LPCITEMIDLIST pidl);
	LPITEMIDLIST LastNavigatedLocation(void) const;
#endif

	virtual bool PreferNativeRenderer(void) const;
	virtual void SetPreferNativeRenderer(bool b);

	virtual bool UsePreviewCache(void) const;
	virtual void SetUsePreviewCache(bool b);

	virtual bool UseQuickInitialPreview(void) const;
	virtual void SetUseQuickInitialPreview(bool b);

	virtual bool UsePreview(void) const;

	virtual bool UseRenderedPreview(void) const;

	virtual bool ShowDetailsPanel(void) const;
	virtual void SetShowDetailsPanel(bool b);

	virtual ON_wString PreferredUnpackFolder(void) const;
	virtual void SetPreferredUnpackFolder(const wchar_t* wszPath);

	virtual bool CheckSupportFilesBeforeRendering(void) const;
	virtual void SetCheckSupportFilesBeforeRendering(bool b);

	// 14th Aug 2019 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-54021
	// 19th Sep 2019 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-54844
	RhRdkSmartMergeChoice SmartMergeChoice(bool bIsPaste) const;
	void SetSmartMergeChoice(bool bIsPaste, RhRdkSmartMergeChoice smc);

	// 15th Oct 2019 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-54940
	bool CombineSimilarTextures(void) const;
	void SetCombineSimilarTextures(bool b);

	// 22nd June 2020 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-58087
	ON_wString GetLastSavedRenderFileExtension(void) const;
	void SetLastSavedRenderFileExtension(const wchar_t* wszExt);

	virtual bool AutoSaveRenderings(void) const;
	virtual void SetAutoSaveRenderings(bool b);

	virtual int AutoSaveKeepAmount(void) const;
	virtual void SetAutoSaveKeepAmount(int value);

	virtual int MaxPreviewCacheMB(void) const;
	virtual int MaxPreviewSeconds(void) const;

	virtual bool EnablePreviewJobLog(void) const;

	virtual COLORREF DarkPreviewCheckerColor(void) const;
	virtual COLORREF LightPreviewCheckerColor(void) const;

	bool EmbedFilesDocumentDefault(void) const;
	void SetEmbedFilesDocumentDefault(bool b);

	bool NeverEmbedFiles(void) const;
	void SetNeverEmbedFiles(bool b);

	bool AlwaysUnpackEmbeddedFilesToTemp(void) const;
	void SetAlwaysUnpackEmbeddedFilesToTemp(bool b);

	//-1 means "automatic" - typically # of processors - 1;
	int BakingQueueThreads(void) const;
	void SetBakingQueueThreads(int);

	bool SaveCompressedTextureFiles(void) const;
	void SetSaveCompressedTextureFiles(bool b);

	// 0 = adaptive baking quality disabled
	// 100 = bake to level of document tolerance
	// 200 = bake to level of 2.00 * document tolerance
	int AdaptiveBakingQuality(void) const;
	void SetAdaptiveBakingQuality(int);

public: // Sun dialog.
	virtual int LabelFormatLoc(void) const;
	virtual void SetLabelFormatLoc(int value);

	virtual int LabelFormatUTC(void) const;
	virtual void SetLabelFormatUTC(int value);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*);

private:
	enum { off, on, unset };
	static DWORD m_dwPreviewCustomRenderMeshes;
	static DWORD m_dwAlwaysShowSunPreview;
	static DWORD m_dwShowQuickInitialPreview;
};

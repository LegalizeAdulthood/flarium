/// Flarium24View.cpp : implementation of the CFlarium24View class
//

#include "stdafx.h"
#include "Flarium24.h"
#include "Flarium24Doc.h"
#include "Flarium24View.h"
#include "mainfrm.h"
#include <math.h>
#include "external.h"
#include "xysize.h"
#include "fparams.h"
#include "gradient.h"
#include "affine.h"
#include "orient.h"
#include "prtscale.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	ON_COMMAND(ID_SAVE_DIB, OnSaveDib)
/////////////////////////////////////////////////////////////////////////////
// CFlarium24View

IMPLEMENT_DYNCREATE(CFlarium24View, CScrollView)

BEGIN_MESSAGE_MAP(CFlarium24View, CScrollView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CFlarium24View)
	ON_COMMAND(ID_SAVE_DIB, OnSaveDib)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_IMAGE_SIZE, OnImageSize)
	ON_COMMAND(ID_WINDOW_SIZEDESKTOP, OnWindowSizedesktop)
	ON_COMMAND(ID_VIEW_MANDEL, OnViewMandel)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MANDEL, OnUpdateViewMandel)
	ON_COMMAND(ID_DRAW_1, OnDraw1)
	ON_UPDATE_COMMAND_UI(ID_DRAW_1, OnUpdateDraw1)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM, OnUpdateViewZoom)
	ON_COMMAND(ID_VIEW_NEW, OnViewNew)
	ON_COMMAND(ID_FILE_LOADPARAMETERS, OnFileLoadparameters)
	ON_COMMAND(ID_FILE_SAVEPARAMETERS, OnFileSaveparameters)
	ON_COMMAND(ID_EDIT_UNDOFRACTALSELECTION, OnEditUndofractalselection)
	ON_COMMAND(ID_IMAGE_PARAMS, OnImageParams)
	ON_COMMAND(ID_DRAW_ABORT, OnDrawAbort)
	ON_COMMAND(ID_DRAW_INVERT, OnDrawInvert)
	ON_UPDATE_COMMAND_UI(ID_DRAW_INVERT, OnUpdateDrawInvert)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEW, OnUpdateViewNew)
	ON_COMMAND(ID_FILTER_1, OnFilter1)
	ON_UPDATE_COMMAND_UI(ID_FILTER_1, OnUpdateFilter1)
	ON_COMMAND(ID_FILTER_0NONE, OnFilter0none)
	ON_UPDATE_COMMAND_UI(ID_FILTER_0NONE, OnUpdateFilter0none)
	ON_COMMAND(ID_FILTER_2, OnFilter2)
	ON_UPDATE_COMMAND_UI(ID_FILTER_2, OnUpdateFilter2)
	ON_COMMAND(ID_FILTER_3, OnFilter3)
	ON_UPDATE_COMMAND_UI(ID_FILTER_3, OnUpdateFilter3)
	ON_COMMAND(ID_FILTER_4, OnFilter4)
	ON_UPDATE_COMMAND_UI(ID_FILTER_4, OnUpdateFilter4)
	ON_COMMAND(ID_FILTER_5, OnFilter5)
	ON_UPDATE_COMMAND_UI(ID_FILTER_5, OnUpdateFilter5)
	ON_COMMAND(ID_FILTER_6, OnFilter6)
	ON_UPDATE_COMMAND_UI(ID_FILTER_6, OnUpdateFilter6)
	ON_COMMAND(ID_DRAW_0, OnDraw0)
	ON_UPDATE_COMMAND_UI(ID_DRAW_0, OnUpdateDraw0)
	ON_COMMAND(ID_DRAW_2, OnDraw2)
	ON_UPDATE_COMMAND_UI(ID_DRAW_2, OnUpdateDraw2)
	ON_COMMAND(ID_DRAW_3, OnDraw3)
	ON_UPDATE_COMMAND_UI(ID_DRAW_3, OnUpdateDraw3)
	ON_COMMAND(ID_DRAW_4, OnDraw4)
	ON_UPDATE_COMMAND_UI(ID_DRAW_4, OnUpdateDraw4)
	ON_COMMAND(ID_DRAW_5, OnDraw5)
	ON_UPDATE_COMMAND_UI(ID_DRAW_5, OnUpdateDraw5)
	ON_COMMAND(ID_DRAW_6, OnDraw6)
	ON_UPDATE_COMMAND_UI(ID_DRAW_6, OnUpdateDraw6)
	ON_COMMAND(ID_DRAW_7, OnDraw7)
	ON_UPDATE_COMMAND_UI(ID_DRAW_7, OnUpdateDraw7)
	ON_COMMAND(ID_DRAW_8, OnDraw8)
	ON_UPDATE_COMMAND_UI(ID_DRAW_8, OnUpdateDraw8)
	ON_COMMAND(ID_DRAW_9, OnDraw9)
	ON_UPDATE_COMMAND_UI(ID_DRAW_9, OnUpdateDraw9)
	ON_COMMAND(ID_DRAW_10, OnDraw10)
	ON_UPDATE_COMMAND_UI(ID_DRAW_10, OnUpdateDraw10)
	ON_COMMAND(ID_IMAGE_COLORPARAMETERS, OnImageColorparameters)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_COLORPARAMETERS, OnUpdateImageColorparameters)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ABORT, OnUpdateDrawAbort)
	ON_COMMAND(ID_DRAW_ORIENTATION, OnDrawOrientation)
	ON_COMMAND(ID_VIEW_JULIA1, OnViewJulia1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_JULIA1, OnUpdateViewJulia1)
	ON_COMMAND(ID_DRAW_ZEROINIT, OnDrawZeroinit)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ZEROINIT, OnUpdateDrawZeroinit)
	ON_COMMAND(ID_DRAW_11, OnDraw11)
	ON_UPDATE_COMMAND_UI(ID_DRAW_11, OnUpdateDraw11)
	ON_COMMAND(ID_DRAW_12, OnDraw12)
	ON_UPDATE_COMMAND_UI(ID_DRAW_12, OnUpdateDraw12)
	ON_COMMAND(ID_DRAW_13, OnDraw13)
	ON_UPDATE_COMMAND_UI(ID_DRAW_13, OnUpdateDraw13)
	ON_COMMAND(ID_DRAW_14, OnDraw14)
	ON_UPDATE_COMMAND_UI(ID_DRAW_14, OnUpdateDraw14)
	ON_COMMAND(ID_DRAW_15, OnDraw15)
	ON_UPDATE_COMMAND_UI(ID_DRAW_15, OnUpdateDraw15)
	ON_COMMAND(ID_DRAW_16, OnDraw16)
	ON_UPDATE_COMMAND_UI(ID_DRAW_16, OnUpdateDraw16)
	ON_COMMAND(ID_DRAW_17, OnDraw17)
	ON_UPDATE_COMMAND_UI(ID_DRAW_17, OnUpdateDraw17)
	ON_COMMAND(ID_DRAW_18, OnDraw18)
	ON_UPDATE_COMMAND_UI(ID_DRAW_18, OnUpdateDraw18)
	ON_COMMAND(ID_DRAW_19, OnDraw19)
	ON_UPDATE_COMMAND_UI(ID_DRAW_19, OnUpdateDraw19)
	ON_COMMAND(ID_DRAW_20, OnDraw20)
	ON_UPDATE_COMMAND_UI(ID_DRAW_20, OnUpdateDraw20)
	ON_COMMAND(ID_DRAW_21, OnDraw21)
	ON_UPDATE_COMMAND_UI(ID_DRAW_21, OnUpdateDraw21)
	ON_COMMAND(ID_DRAW_22, OnDraw22)
	ON_UPDATE_COMMAND_UI(ID_DRAW_22, OnUpdateDraw22)
	ON_COMMAND(ID_DRAW_23, OnDraw23)
	ON_UPDATE_COMMAND_UI(ID_DRAW_23, OnUpdateDraw23)
	ON_COMMAND(ID_DRAW_24, OnDraw24)
	ON_UPDATE_COMMAND_UI(ID_DRAW_24, OnUpdateDraw24)
	ON_COMMAND(ID_DRAW_25, OnDraw25)
	ON_UPDATE_COMMAND_UI(ID_DRAW_25, OnUpdateDraw25)
	ON_COMMAND(ID_DRAW_26, OnDraw26)
	ON_UPDATE_COMMAND_UI(ID_DRAW_26, OnUpdateDraw26)
	ON_COMMAND(ID_DRAW_27, OnDraw27)
	ON_UPDATE_COMMAND_UI(ID_DRAW_27, OnUpdateDraw27)
	ON_COMMAND(ID_FRACTAL_BIOMORPHNONE, OnFractalBiomorphnone)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_BIOMORPHNONE, OnUpdateFractalBiomorphnone)
	ON_COMMAND(ID_FRACTAL_1BIOMORPHXORY, OnFractal1biomorphxory)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_1BIOMORPHXORY, OnUpdateFractal1biomorphxory)
	ON_COMMAND(ID_FRACTAL_BIOMORPH, OnFractalBiomorph)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_BIOMORPH, OnUpdateFractalBiomorph)
	ON_COMMAND(ID_FRACTAL_BIOMORPHTESTXORY, OnFractalBiomorphtestxory)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_BIOMORPHTESTXORY, OnUpdateFractalBiomorphtestxory)
	ON_COMMAND(ID_FILTER_7, OnFilter7)
	ON_UPDATE_COMMAND_UI(ID_FILTER_7, OnUpdateFilter7)
	ON_COMMAND(ID_FILTER_8, OnFilter8)
	ON_UPDATE_COMMAND_UI(ID_FILTER_8, OnUpdateFilter8)
	ON_COMMAND(ID_FILTER_9, OnFilter9)
	ON_UPDATE_COMMAND_UI(ID_FILTER_9, OnUpdateFilter9)
	ON_COMMAND(ID_FILTER_10, OnFilter10)
	ON_UPDATE_COMMAND_UI(ID_FILTER_10, OnUpdateFilter10)
	ON_COMMAND(ID_FILTER_11, OnFilter11)
	ON_UPDATE_COMMAND_UI(ID_FILTER_11, OnUpdateFilter11)
	ON_COMMAND(ID_FILTER_12, OnFilter12)
	ON_UPDATE_COMMAND_UI(ID_FILTER_12, OnUpdateFilter12)
	ON_COMMAND(ID_COLOUR_0, OnColour0)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_0, OnUpdateColour0)
	ON_COMMAND(ID_COLOUR_1, OnColour1)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_1, OnUpdateColour1)
	ON_COMMAND(ID_COLOUR_2, OnColour2)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_2, OnUpdateColour2)
	ON_COMMAND(ID_COLOUR_3, OnColour3)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_3, OnUpdateColour3)
	ON_COMMAND(ID_COLOUR_4, OnColour4)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_4, OnUpdateColour4)
	ON_COMMAND(ID_COLOUR_5, OnColour5)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_5, OnUpdateColour5)
	ON_COMMAND(ID_COLOUR_6, OnColour6)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_6, OnUpdateColour6)
	ON_COMMAND(ID_COLOUR_7, OnColour7)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_7, OnUpdateColour7)
	ON_WM_TIMER()
	ON_COMMAND(ID_SHIFT_START, OnShiftStart)
	ON_UPDATE_COMMAND_UI(ID_SHIFT_START, OnUpdateShiftStart)
	ON_COMMAND(ID_DRAW_28, OnDraw28)
	ON_UPDATE_COMMAND_UI(ID_DRAW_28, OnUpdateDraw28)
	ON_COMMAND(ID_DRAW_29, OnDraw29)
	ON_UPDATE_COMMAND_UI(ID_DRAW_29, OnUpdateDraw29)
	ON_COMMAND(ID_DRAW_30, OnDraw30)
	ON_UPDATE_COMMAND_UI(ID_DRAW_30, OnUpdateDraw30)
	ON_COMMAND(ID_DRAW_31, OnDraw31)
	ON_UPDATE_COMMAND_UI(ID_DRAW_31, OnUpdateDraw31)
	ON_COMMAND(ID_DRAW_32, OnDraw32)
	ON_UPDATE_COMMAND_UI(ID_DRAW_32, OnUpdateDraw32)
	ON_COMMAND(ID_DRAW_33, OnDraw33)
	ON_UPDATE_COMMAND_UI(ID_DRAW_33, OnUpdateDraw33)
	ON_COMMAND(ID_DRAW_34, OnDraw34)
	ON_UPDATE_COMMAND_UI(ID_DRAW_34, OnUpdateDraw34)
	ON_COMMAND(ID_DRAW_35, OnDraw35)
	ON_UPDATE_COMMAND_UI(ID_DRAW_35, OnUpdateDraw35)
	ON_COMMAND(ID_DRAW_36, OnDraw36)
	ON_UPDATE_COMMAND_UI(ID_DRAW_36, OnUpdateDraw36)
	ON_COMMAND(ID_DRAW_37, OnDraw37)
	ON_UPDATE_COMMAND_UI(ID_DRAW_37, OnUpdateDraw37)
	ON_COMMAND(ID_DRAW_38, OnDraw38)
	ON_UPDATE_COMMAND_UI(ID_DRAW_38, OnUpdateDraw38)
	ON_COMMAND(ID_DRAW_39, OnDraw39)
	ON_UPDATE_COMMAND_UI(ID_DRAW_39, OnUpdateDraw39)
	ON_COMMAND(ID_DRAW_40, OnDraw40)
	ON_UPDATE_COMMAND_UI(ID_DRAW_40, OnUpdateDraw40)
	ON_COMMAND(ID_DRAW_41, OnDraw41)
	ON_UPDATE_COMMAND_UI(ID_DRAW_41, OnUpdateDraw41)
	ON_COMMAND(ID_DRAW_42, OnDraw42)
	ON_UPDATE_COMMAND_UI(ID_DRAW_42, OnUpdateDraw42)
	ON_COMMAND(ID_DRAW_43, OnDraw43)
	ON_UPDATE_COMMAND_UI(ID_DRAW_43, OnUpdateDraw43)
	ON_COMMAND(ID_DRAW_44, OnDraw44)
	ON_UPDATE_COMMAND_UI(ID_DRAW_44, OnUpdateDraw44)
	ON_COMMAND(ID_DRAW_45, OnDraw45)
	ON_UPDATE_COMMAND_UI(ID_DRAW_45, OnUpdateDraw45)
	ON_COMMAND(ID_DRAW_46, OnDraw46)
	ON_UPDATE_COMMAND_UI(ID_DRAW_46, OnUpdateDraw46)
	ON_COMMAND(ID_DRAW_47, OnDraw47)
	ON_UPDATE_COMMAND_UI(ID_DRAW_47, OnUpdateDraw47)
	ON_COMMAND(ID_DRAW_48, OnDraw48)
	ON_UPDATE_COMMAND_UI(ID_DRAW_48, OnUpdateDraw48)
	ON_COMMAND(ID_DRAW_49, OnDraw49)
	ON_UPDATE_COMMAND_UI(ID_DRAW_49, OnUpdateDraw49)
	ON_COMMAND(ID_DRAW_50, OnDraw50)
	ON_UPDATE_COMMAND_UI(ID_DRAW_50, OnUpdateDraw50)
	ON_COMMAND(ID_FILTER_13, OnFilter13)
	ON_UPDATE_COMMAND_UI(ID_FILTER_13, OnUpdateFilter13)
	ON_COMMAND(ID_FILTER_14, OnFilter14)
	ON_UPDATE_COMMAND_UI(ID_FILTER_14, OnUpdateFilter14)
	ON_COMMAND(ID_FILTER_15, OnFilter15)
	ON_UPDATE_COMMAND_UI(ID_FILTER_15, OnUpdateFilter15)
	ON_COMMAND(ID_FILTER_16, OnFilter16)
	ON_COMMAND(ID_FILTER_17, OnFilter17)
	ON_UPDATE_COMMAND_UI(ID_FILTER_17, OnUpdateFilter17)
	ON_UPDATE_COMMAND_UI(ID_FILTER_16, OnUpdateFilter16)
	ON_COMMAND(ID_FILTER_18, OnFilter18)
	ON_UPDATE_COMMAND_UI(ID_FILTER_18, OnUpdateFilter18)
	ON_COMMAND(ID_FILTER_30, OnFilter30)
	ON_UPDATE_COMMAND_UI(ID_FILTER_30, OnUpdateFilter30)
	ON_COMMAND(ID_FILTER_31, OnFilter31)
	ON_UPDATE_COMMAND_UI(ID_FILTER_31, OnUpdateFilter31)
	ON_COMMAND(ID_FILTER_32, OnFilter32)
	ON_UPDATE_COMMAND_UI(ID_FILTER_32, OnUpdateFilter32)
	ON_COMMAND(ID_FILTER_33, OnFilter33)
	ON_UPDATE_COMMAND_UI(ID_FILTER_33, OnUpdateFilter33)
	ON_COMMAND(ID_FILTER_34, OnFilter34)
	ON_UPDATE_COMMAND_UI(ID_FILTER_34, OnUpdateFilter34)
	ON_COMMAND(ID_FILTER_35, OnFilter35)
	ON_UPDATE_COMMAND_UI(ID_FILTER_35, OnUpdateFilter35)
	ON_COMMAND(ID_FILTER_36, OnFilter36)
	ON_UPDATE_COMMAND_UI(ID_FILTER_36, OnUpdateFilter36)
	ON_COMMAND(ID_FILTER_37, OnFilter37)
	ON_UPDATE_COMMAND_UI(ID_FILTER_37, OnUpdateFilter37)
	ON_COMMAND(ID_FILTER_38, OnFilter38)
	ON_UPDATE_COMMAND_UI(ID_FILTER_38, OnUpdateFilter38)
	ON_COMMAND(ID_FILTER_39, OnFilter39)
	ON_UPDATE_COMMAND_UI(ID_FILTER_39, OnUpdateFilter39)
	ON_COMMAND(ID_FILTER_40, OnFilter40)
	ON_UPDATE_COMMAND_UI(ID_FILTER_40, OnUpdateFilter40)
	ON_COMMAND(ID_FILTER_41, OnFilter41)
	ON_UPDATE_COMMAND_UI(ID_FILTER_41, OnUpdateFilter41)
	ON_COMMAND(ID_FILTER_42, OnFilter42)
	ON_UPDATE_COMMAND_UI(ID_FILTER_42, OnUpdateFilter42)
	ON_COMMAND(ID_FILTER_43, OnFilter43)
	ON_UPDATE_COMMAND_UI(ID_FILTER_43, OnUpdateFilter43)
	ON_COMMAND(ID_FILTER_44, OnFilter44)
	ON_UPDATE_COMMAND_UI(ID_FILTER_44, OnUpdateFilter44)
	ON_COMMAND(ID_FILTER_45, OnFilter45)
	ON_UPDATE_COMMAND_UI(ID_FILTER_45, OnUpdateFilter45)
	ON_COMMAND(ID_FILTER_46, OnFilter46)
	ON_UPDATE_COMMAND_UI(ID_FILTER_46, OnUpdateFilter46)
	ON_COMMAND(ID_FILTER_47, OnFilter47)
	ON_UPDATE_COMMAND_UI(ID_FILTER_47, OnUpdateFilter47)
	ON_COMMAND(ID_FILTER_48, OnFilter48)
	ON_UPDATE_COMMAND_UI(ID_FILTER_48, OnUpdateFilter48)
	ON_COMMAND(ID_FILTER_49, OnFilter49)
	ON_UPDATE_COMMAND_UI(ID_FILTER_49, OnUpdateFilter49)
	ON_COMMAND(ID_FILTER_50, OnFilter50)
	ON_UPDATE_COMMAND_UI(ID_FILTER_50, OnUpdateFilter50)
	ON_COMMAND(ID_FILTER_51, OnFilter51)
	ON_UPDATE_COMMAND_UI(ID_FILTER_51, OnUpdateFilter51)
	ON_COMMAND(ID_FILTER_52, OnFilter52)
	ON_UPDATE_COMMAND_UI(ID_FILTER_52, OnUpdateFilter52)
	ON_COMMAND(ID_FILTER_53, OnFilter53)
	ON_UPDATE_COMMAND_UI(ID_FILTER_53, OnUpdateFilter53)
	ON_COMMAND(ID_DRAW_51, OnDraw51)
	ON_UPDATE_COMMAND_UI(ID_DRAW_51, OnUpdateDraw51)
	ON_COMMAND(ID_DRAW_52, OnDraw52)
	ON_UPDATE_COMMAND_UI(ID_DRAW_52, OnUpdateDraw52)
	ON_COMMAND(ID_DRAW_53, OnDraw53)
	ON_UPDATE_COMMAND_UI(ID_DRAW_53, OnUpdateDraw53)
	ON_COMMAND(ID_DRAW_54, OnDraw54)
	ON_UPDATE_COMMAND_UI(ID_DRAW_54, OnUpdateDraw54)
	ON_COMMAND(ID_DRAW_55, OnDraw55)
	ON_UPDATE_COMMAND_UI(ID_DRAW_55, OnUpdateDraw55)
	ON_COMMAND(ID_DRAW_56, OnDraw56)
	ON_UPDATE_COMMAND_UI(ID_DRAW_56, OnUpdateDraw56)
	ON_COMMAND(ID_DRAW_57, OnDraw57)
	ON_UPDATE_COMMAND_UI(ID_DRAW_57, OnUpdateDraw57)
	ON_COMMAND(ID_DRAW_58, OnDraw58)
	ON_UPDATE_COMMAND_UI(ID_DRAW_58, OnUpdateDraw58)
	ON_COMMAND(ID_DRAW_59, OnDraw59)
	ON_UPDATE_COMMAND_UI(ID_DRAW_59, OnUpdateDraw59)
	ON_COMMAND(ID_DRAW_60, OnDraw60)
	ON_UPDATE_COMMAND_UI(ID_DRAW_60, OnUpdateDraw60)
	ON_COMMAND(ID_OPTIONS_1, OnOptions1)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_1, OnUpdateOptions1)
	ON_COMMAND(ID_OPTIONS_10, OnOptions10)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_10, OnUpdateOptions10)
	ON_COMMAND(ID_OPTIONS_2, OnOptions2)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_2, OnUpdateOptions2)
	ON_COMMAND(ID_OPTIONS_3, OnOptions3)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_3, OnUpdateOptions3)
	ON_COMMAND(ID_OPTIONS_4, OnOptions4)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_4, OnUpdateOptions4)
	ON_COMMAND(ID_OPTIONS_5, OnOptions5)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_5, OnUpdateOptions5)
	ON_COMMAND(ID_OPTIONS_6, OnOptions6)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_6, OnUpdateOptions6)
	ON_COMMAND(ID_OPTIONS_7, OnOptions7)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_7, OnUpdateOptions7)
	ON_COMMAND(ID_OPTIONS_8, OnOptions8)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_8, OnUpdateOptions8)
	ON_COMMAND(ID_OPTIONS_9, OnOptions9)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_9, OnUpdateOptions9)
	ON_COMMAND(ID_DRAW_61, OnDraw61)
	ON_UPDATE_COMMAND_UI(ID_DRAW_61, OnUpdateDraw61)
	ON_COMMAND(ID_DRAW_62, OnDraw62)
	ON_UPDATE_COMMAND_UI(ID_DRAW_62, OnUpdateDraw62)
	ON_COMMAND(ID_DRAW_63, OnDraw63)
	ON_UPDATE_COMMAND_UI(ID_DRAW_63, OnUpdateDraw63)
	ON_COMMAND(ID_DRAW_64, OnDraw64)
	ON_UPDATE_COMMAND_UI(ID_DRAW_64, OnUpdateDraw64)
	ON_COMMAND(ID_COLOUR_8, OnColour8)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_8, OnUpdateColour8)
	ON_COMMAND(ID_COLOUR_9, OnColour9)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_9, OnUpdateColour9)
	ON_COMMAND(ID_COLOUR_10, OnColour10)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_10, OnUpdateColour10)
	ON_COMMAND(ID_COLOUR_11, OnColour11)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_11, OnUpdateColour11)
	ON_COMMAND(ID_COLOUR_12, OnColour12)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_12, OnUpdateColour12)
	ON_COMMAND(ID_FILTER_54, OnFilter54)
	ON_UPDATE_COMMAND_UI(ID_FILTER_54, OnUpdateFilter54)
	ON_COMMAND(ID_FILTER_55, OnFilter55)
	ON_UPDATE_COMMAND_UI(ID_FILTER_55, OnUpdateFilter55)
	ON_COMMAND(ID_FILTER_56, OnFilter56)
	ON_UPDATE_COMMAND_UI(ID_FILTER_56, OnUpdateFilter56)
	ON_COMMAND(ID_COLOUR_13, OnColour13)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_13, OnUpdateColour13)
	ON_COMMAND(ID_COLOUR_14, OnColour14)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_14, OnUpdateColour14)
	ON_COMMAND(ID_DRAW_65, OnDraw65)
	ON_UPDATE_COMMAND_UI(ID_DRAW_65, OnUpdateDraw65)
	ON_COMMAND(ID_DRAW_66, OnDraw66)
	ON_UPDATE_COMMAND_UI(ID_DRAW_66, OnUpdateDraw66)
	ON_COMMAND(ID_DRAW_67, OnDraw67)
	ON_UPDATE_COMMAND_UI(ID_DRAW_67, OnUpdateDraw67)
	ON_COMMAND(ID_DRAW_68, OnDraw68)
	ON_UPDATE_COMMAND_UI(ID_DRAW_68, OnUpdateDraw68)
	ON_COMMAND(ID_DRAW_69, OnDraw69)
	ON_UPDATE_COMMAND_UI(ID_DRAW_69, OnUpdateDraw69)
	ON_COMMAND(ID_DRAW_70, OnDraw70)
	ON_UPDATE_COMMAND_UI(ID_DRAW_70, OnUpdateDraw70)
	ON_COMMAND(ID_DRAW_71, OnDraw71)
	ON_UPDATE_COMMAND_UI(ID_DRAW_71, OnUpdateDraw71)
	ON_COMMAND(ID_DRAW_72, OnDraw72)
	ON_UPDATE_COMMAND_UI(ID_DRAW_72, OnUpdateDraw72)
	ON_COMMAND(ID_DRAW_73, OnDraw73)
	ON_UPDATE_COMMAND_UI(ID_DRAW_73, OnUpdateDraw73)
	ON_COMMAND(ID_DRAW_74, OnDraw74)
	ON_UPDATE_COMMAND_UI(ID_DRAW_74, OnUpdateDraw74)
	ON_COMMAND(ID_DRAW_75, OnDraw75)
	ON_UPDATE_COMMAND_UI(ID_DRAW_75, OnUpdateDraw75)
	ON_COMMAND(ID_DRAW_76, OnDraw76)
	ON_UPDATE_COMMAND_UI(ID_DRAW_76, OnUpdateDraw76)
	ON_COMMAND(ID_DRAW_77, OnDraw77)
	ON_UPDATE_COMMAND_UI(ID_DRAW_77, OnUpdateDraw77)
	ON_COMMAND(ID_DRAW_78, OnDraw78)
	ON_UPDATE_COMMAND_UI(ID_DRAW_78, OnUpdateDraw78)
	ON_COMMAND(ID_DRAW_79, OnDraw79)
	ON_UPDATE_COMMAND_UI(ID_DRAW_79, OnUpdateDraw79)
	ON_COMMAND(ID_DRAW_80, OnDraw80)
	ON_UPDATE_COMMAND_UI(ID_DRAW_80, OnUpdateDraw80)
	ON_COMMAND(ID_DRAW_81, OnDraw81)
	ON_UPDATE_COMMAND_UI(ID_DRAW_81, OnUpdateDraw81)
	ON_COMMAND(ID_DRAW_82, OnDraw82)
	ON_UPDATE_COMMAND_UI(ID_DRAW_82, OnUpdateDraw82)
	ON_COMMAND(ID_DRAW_83, OnDraw83)
	ON_UPDATE_COMMAND_UI(ID_DRAW_83, OnUpdateDraw83)
	ON_COMMAND(ID_DRAW_84, OnDraw84)
	ON_UPDATE_COMMAND_UI(ID_DRAW_84, OnUpdateDraw84)
	ON_COMMAND(ID_DRAW_85, OnDraw85)
	ON_UPDATE_COMMAND_UI(ID_DRAW_85, OnUpdateDraw85)
	ON_COMMAND(ID_DRAW_86, OnDraw86)
	ON_UPDATE_COMMAND_UI(ID_DRAW_86, OnUpdateDraw86)
	ON_COMMAND(ID_DRAW_87, OnDraw87)
	ON_UPDATE_COMMAND_UI(ID_DRAW_87, OnUpdateDraw87)
	ON_COMMAND(ID_DRAW_88, OnDraw88)
	ON_UPDATE_COMMAND_UI(ID_DRAW_88, OnUpdateDraw88)
	ON_COMMAND(ID_DRAW_89, OnDraw89)
	ON_UPDATE_COMMAND_UI(ID_DRAW_89, OnUpdateDraw89)
	ON_COMMAND(ID_DRAW_90, OnDraw90)
	ON_UPDATE_COMMAND_UI(ID_DRAW_90, OnUpdateDraw90)
	ON_COMMAND(ID_DRAW_91, OnDraw91)
	ON_UPDATE_COMMAND_UI(ID_DRAW_91, OnUpdateDraw91)
	ON_COMMAND(ID_DRAW_92, OnDraw92)
	ON_UPDATE_COMMAND_UI(ID_DRAW_92, OnUpdateDraw92)
	ON_COMMAND(ID_DRAW_93, OnDraw93)
	ON_UPDATE_COMMAND_UI(ID_DRAW_93, OnUpdateDraw93)
	ON_COMMAND(ID_DRAW_MSETMETHOD, OnDrawMsetmethod)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MSETMETHOD, OnUpdateDrawMsetmethod)
	ON_COMMAND(ID_FILE_LOADCOLORS, OnFileLoadcolors)
	ON_COMMAND(ID_FILE_SAVECOLORS, OnFileSavecolors)
	ON_COMMAND(ID_DRAW_94, OnDraw94)
	ON_UPDATE_COMMAND_UI(ID_DRAW_94, OnUpdateDraw94)
	ON_COMMAND(ID_DRAW_95, OnDraw95)
	ON_UPDATE_COMMAND_UI(ID_DRAW_95, OnUpdateDraw95)
	ON_COMMAND(ID_DRAW_96, OnDraw96)
	ON_UPDATE_COMMAND_UI(ID_DRAW_96, OnUpdateDraw96)
	ON_COMMAND(ID_DRAW_97, OnDraw97)
	ON_UPDATE_COMMAND_UI(ID_DRAW_97, OnUpdateDraw97)
	ON_COMMAND(ID_DRAW_98, OnDraw98)
	ON_UPDATE_COMMAND_UI(ID_DRAW_98, OnUpdateDraw98)
	ON_COMMAND(ID_DRAW_99, OnDraw99)
	ON_UPDATE_COMMAND_UI(ID_DRAW_99, OnUpdateDraw99)
	ON_COMMAND(ID_DRAW_100, OnDraw100)
	ON_UPDATE_COMMAND_UI(ID_DRAW_100, OnUpdateDraw100)
	ON_COMMAND(ID_DRAW_101, OnDraw101)
	ON_UPDATE_COMMAND_UI(ID_DRAW_101, OnUpdateDraw101)
	ON_COMMAND(ID_DRAW_102, OnDraw102)
	ON_UPDATE_COMMAND_UI(ID_DRAW_102, OnUpdateDraw102)
	ON_COMMAND(ID_DRAW_103, OnDraw103)
	ON_UPDATE_COMMAND_UI(ID_DRAW_103, OnUpdateDraw103)
	ON_COMMAND(ID_DRAW_104, OnDraw104)
	ON_UPDATE_COMMAND_UI(ID_DRAW_104, OnUpdateDraw104)
	ON_COMMAND(ID_DRAW_105, OnDraw105)
	ON_UPDATE_COMMAND_UI(ID_DRAW_105, OnUpdateDraw105)
	ON_COMMAND(ID_DRAW_106, OnDraw106)
	ON_UPDATE_COMMAND_UI(ID_DRAW_106, OnUpdateDraw106)
	ON_COMMAND(ID_DRAW_107, OnDraw107)
	ON_UPDATE_COMMAND_UI(ID_DRAW_107, OnUpdateDraw107)
	ON_COMMAND(ID_DRAW_108, OnDraw108)
	ON_UPDATE_COMMAND_UI(ID_DRAW_108, OnUpdateDraw108)
	ON_COMMAND(ID_DRAW_109, OnDraw109)
	ON_UPDATE_COMMAND_UI(ID_DRAW_109, OnUpdateDraw109)
	ON_COMMAND(ID_DRAW_110, OnDraw110)
	ON_UPDATE_COMMAND_UI(ID_DRAW_110, OnUpdateDraw110)
	ON_COMMAND(ID_FILTER3_57, OnFilter357)
	ON_UPDATE_COMMAND_UI(ID_FILTER3_57, OnUpdateFilter357)
	ON_COMMAND(ID_FILTER3_58, OnFilter358)
	ON_UPDATE_COMMAND_UI(ID_FILTER3_58, OnUpdateFilter358)
	ON_COMMAND(ID_FILTER3_59, OnFilter359)
	ON_UPDATE_COMMAND_UI(ID_FILTER3_59, OnUpdateFilter359)
	ON_COMMAND(ID_FILTER3_60, OnFilter360)
	ON_UPDATE_COMMAND_UI(ID_FILTER3_60, OnUpdateFilter360)
	ON_COMMAND(ID_FILTER_61, OnFilter61)
	ON_UPDATE_COMMAND_UI(ID_FILTER_61, OnUpdateFilter61)
	ON_COMMAND(ID_FILTER_62, OnFilter62)
	ON_UPDATE_COMMAND_UI(ID_FILTER_62, OnUpdateFilter62)
	ON_COMMAND(ID_FILTER_63, OnFilter63)
	ON_UPDATE_COMMAND_UI(ID_FILTER_63, OnUpdateFilter63)
	ON_COMMAND(ID_FILTER_64, OnFilter64)
	ON_UPDATE_COMMAND_UI(ID_FILTER_64, OnUpdateFilter64)
	ON_COMMAND(ID_FILTER_65, OnFilter65)
	ON_UPDATE_COMMAND_UI(ID_FILTER_65, OnUpdateFilter65)
	ON_COMMAND(ID_FILTER_66, OnFilter66)
	ON_UPDATE_COMMAND_UI(ID_FILTER_66, OnUpdateFilter66)
	ON_COMMAND(ID_FILTER_67, OnFilter67)
	ON_UPDATE_COMMAND_UI(ID_FILTER_67, OnUpdateFilter67)
	ON_COMMAND(ID_FILTER_68, OnFilter68)
	ON_UPDATE_COMMAND_UI(ID_FILTER_68, OnUpdateFilter68)
	ON_COMMAND(ID_DRAW_111, OnDraw111)
	ON_UPDATE_COMMAND_UI(ID_DRAW_111, OnUpdateDraw111)
	ON_COMMAND(ID_FILE_PRINTSCALING, OnFilePrintscaling)
	ON_COMMAND(ID_COLOUR_15, OnColour15)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_15, OnUpdateColour15)
	ON_COMMAND(ID_COLOUR_16, OnColour16)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_16, OnUpdateColour16)
	ON_COMMAND(ID_COLOUR_17, OnColour17)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_17, OnUpdateColour17)
	ON_COMMAND(ID_COLOUR_18, OnColour18)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_18, OnUpdateColour18)
	ON_COMMAND(ID_DRAW_112, OnDraw112)
	ON_UPDATE_COMMAND_UI(ID_DRAW_112, OnUpdateDraw112)
	ON_COMMAND(ID_DRAW_113, OnDraw113)
	ON_UPDATE_COMMAND_UI(ID_DRAW_113, OnUpdateDraw113)
	ON_COMMAND(ID_DRAW_114, OnDraw114)
	ON_UPDATE_COMMAND_UI(ID_DRAW_114, OnUpdateDraw114)
	ON_COMMAND(ID_DRAW_115, OnDraw115)
	ON_UPDATE_COMMAND_UI(ID_DRAW_115, OnUpdateDraw115)
	ON_COMMAND(ID_DRAW_116, OnDraw116)
	ON_UPDATE_COMMAND_UI(ID_DRAW_116, OnUpdateDraw116)
	ON_COMMAND(ID_DRAW_BIOMORPH_4, OnDrawBiomorph4)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BIOMORPH_4, OnUpdateDrawBiomorph4)
	ON_COMMAND(ID_DRAW_BIOMORPH_5, OnDrawBiomorph5)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BIOMORPH_5, OnUpdateDrawBiomorph5)
	ON_COMMAND(ID_DRAW_BIOMORPH_6, OnDrawBiomorph6)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BIOMORPH_6, OnUpdateDrawBiomorph6)
	ON_COMMAND(ID_DRAW_FSET, OnDrawFset)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FSET, OnUpdateDrawFset)
	ON_COMMAND(ID_COLOUR_19, OnColour19)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_19, OnUpdateColour19)
	ON_COMMAND(ID_COLOUR_20, OnColour20)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_20, OnUpdateColour20)
	ON_COMMAND(ID_COLOUR_21, OnColour21)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_21, OnUpdateColour21)
	ON_COMMAND(ID_COLOUR_22, OnColour22)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_22, OnUpdateColour22)
	ON_COMMAND(ID_VIEW_STRETCHTOFIT, OnViewStretchtofit)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STRETCHTOFIT, OnUpdateViewStretchtofit)
	ON_COMMAND(ID_FILTER_69, OnFilter69)
	ON_UPDATE_COMMAND_UI(ID_FILTER_69, OnUpdateFilter69)
	ON_COMMAND(ID_DRAW_120, OnDraw120)
	ON_UPDATE_COMMAND_UI(ID_DRAW_120, OnUpdateDraw120)
	ON_COMMAND(ID_DRAW_121, OnDraw121)
	ON_UPDATE_COMMAND_UI(ID_DRAW_121, OnUpdateDraw121)
	ON_COMMAND(ID_DRAW_122, OnDraw122)
	ON_UPDATE_COMMAND_UI(ID_DRAW_122, OnUpdateDraw122)
	ON_COMMAND(ID_DRAW_123, OnDraw123)
	ON_UPDATE_COMMAND_UI(ID_DRAW_123, OnUpdateDraw123)
	ON_COMMAND(ID_DRAW_LATOOFDLG, OnDrawLatoofdlg)
	ON_COMMAND(ID_DRAW_AFFINETRANSFORMATION, OnDrawAffinetransformation)
	ON_COMMAND(ID_DRAW_REPEAT, OnDrawRepeat)
	ON_COMMAND(ID_IMAGE_BACKGROUNDCOLOR, OnImageBackgroundcolor)
	ON_COMMAND(ID_DRAW_117, OnDraw117)
	ON_UPDATE_COMMAND_UI(ID_DRAW_117, OnUpdateDraw117)
	ON_COMMAND(ID_DRAW_124, OnDraw124)
	ON_UPDATE_COMMAND_UI(ID_DRAW_124, OnUpdateDraw124)
	ON_COMMAND(ID_DRAW_118, OnDraw118)
	ON_UPDATE_COMMAND_UI(ID_DRAW_118, OnUpdateDraw118)
	ON_COMMAND(ID_DRAW_119, OnDraw119)
	ON_UPDATE_COMMAND_UI(ID_DRAW_119, OnUpdateDraw119)
	ON_COMMAND(ID_DRAW_125, OnDraw125)
	ON_UPDATE_COMMAND_UI(ID_DRAW_125, OnUpdateDraw125)
	ON_COMMAND(ID_DRAW_126, OnDraw126)
	ON_UPDATE_COMMAND_UI(ID_DRAW_126, OnUpdateDraw126)
	ON_COMMAND(ID_DRAW_127, OnDraw127)
	ON_UPDATE_COMMAND_UI(ID_DRAW_127, OnUpdateDraw127)
	ON_COMMAND(ID_DRAW_128, OnDraw128)
	ON_UPDATE_COMMAND_UI(ID_DRAW_128, OnUpdateDraw128)
	ON_COMMAND(ID_DRAW_129, OnDraw129)
	ON_UPDATE_COMMAND_UI(ID_DRAW_129, OnUpdateDraw129)
	ON_COMMAND(ID_DRAW_130, OnDraw130)
	ON_UPDATE_COMMAND_UI(ID_DRAW_130, OnUpdateDraw130)
	ON_COMMAND(ID_DRAW_131, OnDraw131)
	ON_UPDATE_COMMAND_UI(ID_DRAW_131, OnUpdateDraw131)
	ON_COMMAND(ID_ATTRACTORS_XY, OnAttractorsXy)
	ON_UPDATE_COMMAND_UI(ID_ATTRACTORS_XY, OnUpdateAttractorsXy)
	ON_COMMAND(ID_ATTRACTORS_XZ, OnAttractorsXz)
	ON_UPDATE_COMMAND_UI(ID_ATTRACTORS_XZ, OnUpdateAttractorsXz)
	ON_COMMAND(ID_ATTRACTORS_YZ, OnAttractorsYz)
	ON_UPDATE_COMMAND_UI(ID_ATTRACTORS_YZ, OnUpdateAttractorsYz)
	ON_COMMAND(ID_DRAW_133, OnDraw133)
	ON_UPDATE_COMMAND_UI(ID_DRAW_133, OnUpdateDraw133)
	ON_COMMAND(ID_DRAW_134, OnDraw134)
	ON_UPDATE_COMMAND_UI(ID_DRAW_134, OnUpdateDraw134)
	ON_COMMAND(ID_DRAW_135, OnDraw135)
	ON_UPDATE_COMMAND_UI(ID_DRAW_135, OnUpdateDraw135)
	ON_COMMAND(ID_DRAW_136, OnDraw136)
	ON_UPDATE_COMMAND_UI(ID_DRAW_136, OnUpdateDraw136)
	ON_COMMAND(ID_DRAW_137, OnDraw137)
	ON_UPDATE_COMMAND_UI(ID_DRAW_137, OnUpdateDraw137)
	ON_COMMAND(ID_DRAW_138, OnDraw138)
	ON_UPDATE_COMMAND_UI(ID_DRAW_138, OnUpdateDraw138)
	ON_COMMAND(ID_DRAW_QUATERNIONPARAMETERS, OnDrawQuaternionparameters)
	ON_UPDATE_COMMAND_UI(ID_DRAW_AFFINETRANSFORMATION, OnUpdateDrawAffinetransformation)
	ON_COMMAND(ID_DRAW_UNIQUE, OnDrawUnique)
	ON_COMMAND(ID_DRAW_140, OnDraw140)
	ON_UPDATE_COMMAND_UI(ID_DRAW_140, OnUpdateDraw140)
	ON_COMMAND(ID_FILTER_70, OnFilter70)
	ON_UPDATE_COMMAND_UI(ID_FILTER_70, OnUpdateFilter70)
	ON_COMMAND(ID_FILTER_71, OnFilter71)
	ON_UPDATE_COMMAND_UI(ID_FILTER_71, OnUpdateFilter71)
	ON_COMMAND(ID_IMAGE_CLEAR, OnImageClear)
	ON_COMMAND(ID_DRAW_141, OnDraw141)
	ON_UPDATE_COMMAND_UI(ID_DRAW_141, OnUpdateDraw141)
	ON_COMMAND(ID_DRAW_142, OnDraw142)
	ON_UPDATE_COMMAND_UI(ID_DRAW_142, OnUpdateDraw142)
	ON_COMMAND(ID_DRAW_143, OnDraw143)
	ON_UPDATE_COMMAND_UI(ID_DRAW_143, OnUpdateDraw143)
	ON_COMMAND(ID_DRAW_144, OnDraw144)
	ON_UPDATE_COMMAND_UI(ID_DRAW_144, OnUpdateDraw144)
	ON_COMMAND(ID_DRAW_145, OnDraw145)
	ON_UPDATE_COMMAND_UI(ID_DRAW_145, OnUpdateDraw145)
	ON_COMMAND(ID_FDIMENSION_VARIATEI, OnFdimensionVariatei)
	ON_UPDATE_COMMAND_UI(ID_FDIMENSION_VARIATEI, OnUpdateFdimensionVariatei)
	ON_COMMAND(ID_IMAGE_ASPECTRATIO, OnImageAspectratio)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ASPECTRATIO, OnUpdateImageAspectratio)
	ON_COMMAND(ID_FILTER3_NOTHINGBUTSTRANDS, OnFilter3Nothingbutstrands)
	ON_UPDATE_COMMAND_UI(ID_FILTER3_NOTHINGBUTSTRANDS, OnUpdateFilter3Nothingbutstrands)
	ON_COMMAND(ID_DRAW_146, OnDraw146)
	ON_UPDATE_COMMAND_UI(ID_DRAW_146, OnUpdateDraw146)
	ON_COMMAND(ID_COLOUR_23, OnColour23)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_23, OnUpdateColour23)
	ON_COMMAND(ID_COLOUR_24, OnColour24)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_24, OnUpdateColour24)
	ON_COMMAND(ID_COLOUR_25, OnColour25)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_25, OnUpdateColour25)
	ON_COMMAND(ID_COLOUR_26, OnColour26)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_26, OnUpdateColour26)
	ON_COMMAND(ID_COLOUR_27, OnColour27)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_27, OnUpdateColour27)
	ON_COMMAND(ID_COLOUR_28, OnColour28)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_28, OnUpdateColour28)
	ON_COMMAND(ID_COLOUR_29, OnColour29)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_29, OnUpdateColour29)
	ON_COMMAND(ID_COLOUR_30, OnColour30)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_30, OnUpdateColour30)
	ON_COMMAND(ID_COLOUR_31, OnColour31)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_31, OnUpdateColour31)
	ON_COMMAND(ID_COLOUR_32, OnColour32)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_32, OnUpdateColour32)
	ON_COMMAND(ID_COLOUR_33, OnColour33)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_33, OnUpdateColour33)
	ON_COMMAND(ID_FILTER_72, OnFilter72)
	ON_UPDATE_COMMAND_UI(ID_FILTER_72, OnUpdateFilter72)
	ON_COMMAND(ID_COLOUR_34, OnColour34)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_34, OnUpdateColour34)
	ON_COMMAND(ID_COLOUR_35, OnColour35)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_35, OnUpdateColour35)
	ON_COMMAND(ID_COLOUR_36, OnColour36)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_36, OnUpdateColour36)
	ON_COMMAND(ID_COLOUR_37, OnColour37)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_37, OnUpdateColour37)
	ON_COMMAND(ID_FILTER_73, OnFilter73)
	ON_UPDATE_COMMAND_UI(ID_FILTER_73, OnUpdateFilter73)
	ON_COMMAND(ID_FILTER_74, OnFilter74)
	ON_UPDATE_COMMAND_UI(ID_FILTER_74, OnUpdateFilter74)
	ON_COMMAND(ID_COLOUR_38, OnColour38)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_38, OnUpdateColour38)
	ON_COMMAND(ID_COLOUR_39, OnColour39)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_39, OnUpdateColour39)
	ON_COMMAND(ID_FILTER_75, OnFilter75)
	ON_UPDATE_COMMAND_UI(ID_FILTER_75, OnUpdateFilter75)
	ON_COMMAND(ID_FILTER_76, OnFilter76)
	ON_UPDATE_COMMAND_UI(ID_FILTER_76, OnUpdateFilter76)
	ON_COMMAND(ID_DRAW_150, OnDraw150)
	ON_UPDATE_COMMAND_UI(ID_DRAW_150, OnUpdateDraw150)
	ON_COMMAND(ID_DRAW_151, OnDraw151)
	ON_UPDATE_COMMAND_UI(ID_DRAW_151, OnUpdateDraw151)
	ON_COMMAND(ID_DRAW_152, OnDraw152)
	ON_UPDATE_COMMAND_UI(ID_DRAW_152, OnUpdateDraw152)
	ON_COMMAND(ID_DRAW_153, OnDraw153)
	ON_UPDATE_COMMAND_UI(ID_DRAW_153, OnUpdateDraw153)
	ON_COMMAND(ID_DRAW_154, OnDraw154)
	ON_UPDATE_COMMAND_UI(ID_DRAW_154, OnUpdateDraw154)
	ON_COMMAND(ID_DRAW_155, OnDraw155)
	ON_UPDATE_COMMAND_UI(ID_DRAW_155, OnUpdateDraw155)
	ON_COMMAND(ID_FILTER_77, OnFilter77)
	ON_UPDATE_COMMAND_UI(ID_FILTER_77, OnUpdateFilter77)
	ON_COMMAND(ID_FILTER_78, OnFilter78)
	ON_UPDATE_COMMAND_UI(ID_FILTER_78, OnUpdateFilter78)
	ON_COMMAND(ID_FILTER_79, OnFilter79)
	ON_UPDATE_COMMAND_UI(ID_FILTER_79, OnUpdateFilter79)
	ON_COMMAND(ID_FILTER_80, OnFilter80)
	ON_UPDATE_COMMAND_UI(ID_FILTER_80, OnUpdateFilter80)
	ON_COMMAND(ID_FILTER_81, OnFilter81)
	ON_UPDATE_COMMAND_UI(ID_FILTER_81, OnUpdateFilter81)
	ON_COMMAND(ID_FILTER_82, OnFilter82)
	ON_UPDATE_COMMAND_UI(ID_FILTER_82, OnUpdateFilter82)
	ON_COMMAND(ID_FILTER_83, OnFilter83)
	ON_UPDATE_COMMAND_UI(ID_FILTER_83, OnUpdateFilter83)
	ON_COMMAND(ID_FILTER_84, OnFilter84)
	ON_UPDATE_COMMAND_UI(ID_FILTER_84, OnUpdateFilter84)
	ON_COMMAND(ID_FILTER_85, OnFilter85)
	ON_UPDATE_COMMAND_UI(ID_FILTER_85, OnUpdateFilter85)
	ON_COMMAND(ID_FILTER_86, OnFilter86)
	ON_UPDATE_COMMAND_UI(ID_FILTER_86, OnUpdateFilter86)
	ON_COMMAND(ID_FILTER_87, OnFilter87)
	ON_UPDATE_COMMAND_UI(ID_FILTER_87, OnUpdateFilter87)
	ON_COMMAND(ID_FILTER_88, OnFilter88)
	ON_UPDATE_COMMAND_UI(ID_FILTER_88, OnUpdateFilter88)
	ON_COMMAND(ID_FILTER_89, OnFilter89)
	ON_UPDATE_COMMAND_UI(ID_FILTER_89, OnUpdateFilter89)
	ON_COMMAND(ID_FILTER_90, OnFilter90)
	ON_UPDATE_COMMAND_UI(ID_FILTER_90, OnUpdateFilter90)
	ON_COMMAND(ID_FILTER_91, OnFilter91)
	ON_UPDATE_COMMAND_UI(ID_FILTER_91, OnUpdateFilter91)
	ON_COMMAND(ID_FILTER_92, OnFilter92)
	ON_UPDATE_COMMAND_UI(ID_FILTER_92, OnUpdateFilter92)
	ON_COMMAND(ID_FILTER_93, OnFilter93)
	ON_UPDATE_COMMAND_UI(ID_FILTER_93, OnUpdateFilter93)
	ON_COMMAND(ID_FILTER_94, OnFilter94)
	ON_UPDATE_COMMAND_UI(ID_FILTER_94, OnUpdateFilter94)
	ON_COMMAND(ID_FILTER_95, OnFilter95)
	ON_UPDATE_COMMAND_UI(ID_FILTER_95, OnUpdateFilter95)
	ON_COMMAND(ID_FILTER_96, OnFilter96)
	ON_UPDATE_COMMAND_UI(ID_FILTER_96, OnUpdateFilter96)
	ON_COMMAND(ID_ORDER_RGB, OnOrderRgb)
	ON_UPDATE_COMMAND_UI(ID_ORDER_RGB, OnUpdateOrderRgb)
	ON_COMMAND(ID_ORDER_RBG, OnOrderRbg)
	ON_UPDATE_COMMAND_UI(ID_ORDER_RBG, OnUpdateOrderRbg)
	ON_COMMAND(ID_ORDER_GRB, OnOrderGrb)
	ON_UPDATE_COMMAND_UI(ID_ORDER_GRB, OnUpdateOrderGrb)
	ON_COMMAND(ID_ORDER_GBR, OnOrderGbr)
	ON_UPDATE_COMMAND_UI(ID_ORDER_GBR, OnUpdateOrderGbr)
	ON_COMMAND(ID_ORDER_BRG, OnOrderBrg)
	ON_UPDATE_COMMAND_UI(ID_ORDER_BRG, OnUpdateOrderBrg)
	ON_COMMAND(ID_ORDER_BGR, OnOrderBgr)
	ON_UPDATE_COMMAND_UI(ID_ORDER_BGR, OnUpdateOrderBgr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	// non-modal dialogs
	ON_MESSAGE(WM_DLGGRADIENT, OnApply_GradView)
	ON_MESSAGE(WM_DLGSHIFT, OnApply_ShiftView)
	ON_MESSAGE(WM_DLGAFFINE, OnApply_AffineView)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlarium24View construction/destruction

CFlarium24View::CFlarium24View()
{
	m_pGradView = new CGradient(this);
	m_pAffineView = new CAffine(this);

	CrtScale = 1;
	PrtScale = 1;

	nImageSize = 0;

	dim.cx = global_width;
	dim.cy = global_height;
	
	dim_save.cx = 0;
	dim_save.cy = 0;
	
	nRedStart = 198;
	nGrnStart = 250;
	nBluStart = 197;

	nRedBack = 0;
	nGrnBack = 0;
	nBluBack = 0;

	uTimer1 = NULL;
	nSpeed = 0;

	nRed = 1;
	nGrn = 2;
	nBlu = 3;

	bRed = NULL;
	bGrn = NULL;
	bBlu = NULL;

	bRedStart = TRUE;
	bGrnStart = TRUE;
	bBluStart = TRUE;

	bGenesisMode = TRUE;

	nColorMethod = 0;
	//bColorChange = FALSE;
	
	min = 0;
	max = 64;

	nBay100  = 1;
	nBay1000 = 1;
	dFilter_12Power  = 5;
	dFilter_12Magnif = 5;
	nFF = 1;
	dStrands = .01;		// .01

	pXTemp = NULL;	// pointer to x temp array
	pYTemp = NULL;  // pointer to y temp array

	//nIter_Data = NULL;
	//mIter_Data = NULL;

	rIter_Data = NULL;
	gIter_Data = NULL;
	bIter_Data = NULL;
	
	//xData = NULL;
	//yData = NULL;

	cOrient.set_real(1);
	cOrient.set_imag(0);

	bDraw	= FALSE;
	bLaunch = FALSE;
	bAbort = FALSE;
	bGradient	= FALSE;
	bAffine	= FALSE;
	dBiomorph = 0;
	ActiveTitle = "";
  bInvertPixel = TRUE;
  bBorder      = TRUE;
	bZeroInit = FALSE;
	bMFilter = FALSE;
	bForward = TRUE;
	bFitToPage = FALSE;
	bPrtParameters_are_set = FALSE;	
	bFDVariate = TRUE;
	bNothingButStrands = FALSE;
	lOffCenter = 0;

	CRMIN  	= -2; //-2.0;			//		// left
	CIMIN  	= -2; //-1.33333;	//    // top
	CRMAX  	=  2; // 1.0;			//	  // right
	CIMAX  	=  2; // 1.33333;	//	  // bottom
	dMagnification = 1;

	dMIN		= 1e-11;
		
	CRMID = CRMID_Finish = ((CRMAX - CRMIN) / 2.0) + CRMIN;
  CIMID	= CIMID_Finish = ((CIMAX - CIMIN) / 2.0) + CIMIN;
 	CRMIN_JUL = -1.5;
	CIMIN_JUL = -1.5;
	CRMAX_JUL =  1.5;
  CIMAX_JUL =  1.5;

	CRMIN_NEW = 0;
	CIMIN_NEW = 0;
	CRMAX_NEW = 0;
  CIMAX_NEW = 0;

	CRMIN_OLD = 0;
	CIMIN_OLD = 0;
	CRMAX_OLD = 0;
  CIMAX_OLD = 0;

	NMAX = JMAX = 128;
	NMAX_Save = 0;
	dBailout = 1000;

	jul 		 = 0;
	jul_save = 1;
	bStartup = TRUE;
	rn = 2;

  mHSize  = AfxGetApp ()->LoadStandardCursor (IDC_UPARROW);
  mHCross = AfxGetApp ()->LoadStandardCursor (IDC_CROSS);
	mWait   = AfxGetApp ()->LoadStandardCursor (IDC_WAIT);

	bTracker = FALSE;
	bStretchToFit = FALSE;
	bAutoTile = FALSE;
	bInvertFractal = FALSE;
  nDistortion = 1;
	//dFInv = 0.5;
	
	bInitialized = FALSE;		
	bMSet = FALSE;
	bFSet = FALSE;

	// Latoocarfian variables
	ma=-1;
	mb=3;

  mc=0.8;
	md=0.8;

	nFilter = 0;
	//me=1;
	mx=0.1;
	my=0.1;																							
    
  latoof_count = 10000;

	// Lorenz vriables
	lx=0.6, ly=0.6, lz=0.6;
	lh=0.001;
	frac = 8.0/3.0;
  
  //lorenz_count = 600000;						  
	nDimension = 0;

	// Default Variables
	rorder_r = 3;
	rorder_i = 0;

	cn.set_real(rorder_r);
	cn.set_imag(rorder_i);
	cr.set_real(2);
	cr.set_imag(0);

	bQuickMode		= FALSE;
	dF28 = 1e-7;  // Quickmode delta factor
	
	// Seed the random-number generator with current time so that
  // the numbers will be different every time we run.
  srand( (unsigned)time( NULL ) );

	hdots = NULL;
	dCloud_top		= 2;
	dCloud_bottom	= -2;
	dCloud_left		= -2;	
	dCloud_right	= 2;			

	// Quaternion variables
	qk1 = .01;
	qk2 = .01;
	qt1 = 0;
	qt2 = 0;

  // Formulae Parser Variables
  u_real = 0;
  v_real = 0;
  w_real = 0;
  z_real = 0;

  u_imag = 0;
  v_imag = 0;
  w_imag = 0;
  z_imag = 0;
  
  strFormulae = "z*z+c";

	nColorOrder = 4;

}

CFlarium24View::~CFlarium24View()
{
	delete m_pGradView;
	delete m_pAffineView;

	if (pXTemp)
		delete pXTemp;
	if (pYTemp)
		delete pYTemp;

	if (bRed)
		delete bRed;
	if (bGrn)
		delete bGrn;
	if (bBlu)
		delete bBlu;

	//if (nIter_Data)
	//	delete nIter_Data;
	//if (mIter_Data)
	//	delete mIter_Data;

	if (rIter_Data)
		delete rIter_Data;
	if (gIter_Data)
		delete gIter_Data;
	if (bIter_Data)
		delete bIter_Data;

	//if (xData)
	//	delete xData;
	//if (yData)
	//	delete yData;

	if (hdots != NULL)
	{
		::GlobalUnlock((HGLOBAL) hdots);
		::GlobalFree((HGLOBAL) hdots);
		hdots = NULL;
	}

}

BOOL CFlarium24View::PreCreateWindow(CREATESTRUCT& cs)
{
	mClassName = AfxRegisterWndClass
		(CS_HREDRAW | CS_VREDRAW,					// Class styles
		0,																// No cursor
		(HBRUSH)::GetStockObject(WHITE_BRUSH),		// Set White background brush
		0);																// No Icon

	cs.lpszClass = mClassName;

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFlarium24View drawing

void CFlarium24View::OnDraw(CDC* pDC)
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	cxDIB = dim.cx;
	cyDIB = dim.cy;

	if (pDoc->m_dib.m_hDrawDib)
	{
		//Set the output and DIB rectangle sizes to be
		//equal to the bitmap size.

		size = pDoc->m_dib.GetSize();	
	
		int cxDIB = size.cx;
		int cyDIB = size.cy;

		DIBRect.left = DIBRect.top = 0;
		DIBRect.right = size.cx;
		DIBRect.bottom = size.cy;    
		outputRect = DIBRect;
				
		if (pDC->IsPrinting())   // printer DC
		{
			pDoc->bPrinting = TRUE;
			// get size of printer page (in pixels)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			
			nXpix = cxPage;
			nYpix = cyPage;
			
			// get printer pixels per inch
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

			if (bFitToPage)
			{	

				//
				// Best Fit case -- create a rectangle which preserves
				// the DIB's aspect ratio, and fills the page horizontally.
				//
				// The formula in the "->bottom" field below calculates the Y
				// position of the printed bitmap, based on the size of the
				// bitmap, the width of the page, and the relative size of
				// a printed pixel (cyInch / cxInch).
				//
				outputRect.top = outputRect.left = 0;
				outputRect.bottom = (int)(((double)DIBRect.bottom * cxPage * cyInch)
					/ ((double)DIBRect.right * cxInch));
				outputRect.right = cxPage;
			}
			else
			{
				if (!bPrtParameters_are_set)				
					OnFilePrintscaling();

				// Calculate the coordinates to center the object
				if (nXpix >= ((double) cxDIB * PrtScale))
				{
					Orig_X = (int) ((double) nXpix/2 - 
										((double) cxDIB * PrtScale)/2);
				}
				else
				{
					Orig_X = 0;
					wsprintf(cstr, "Image Clipped, X printer = %d, X file = %d",
						nXpix, (int) ((double) cxDIB * PrtScale));
					AfxMessageBox(cstr);
				}
			
				if (nYpix >= ((double) cyDIB * PrtScale))
				{
					Orig_Y = (int) ((double) nYpix/2 - 
		  							((double) cyDIB * PrtScale)/2);
				}
				else
				{
					Orig_Y = 0;
					wsprintf(cstr, "Image Clipped, Y printer = %d, Y file = %d",
						nYpix, (int) ((double) cyDIB * PrtScale)); 
					AfxMessageBox(cstr);
			
				}

				outputRect.left  	= Orig_X;
  			outputRect.top   	= Orig_Y;
    		outputRect.right 	= (int) ((double) Orig_X +
     												((double) cxDIB * PrtScale)-1);
    		outputRect.bottom	= (int) ((double) Orig_Y +
    	 											((double) cyDIB * PrtScale)-1);
			
				wsprintf(cstr, "Print Area = Hr=%d,Vr=%d,x=%d,y=%d",
				 	nXpix, nYpix,
				 	(int) ((double)cxDIB*PrtScale),
				 	(int) ((double)cyDIB*PrtScale));
				Status_Bar(cstr);

				screen.cx = nXpix;
				screen.cy = nYpix;
			
			}
		}
		else   // not printer DC
		{
			bPrtParameters_are_set = FALSE;	
			pDoc->bPrinting = FALSE;
			GetClientRect(clientRect); // device coords
			nXpix = clientRect.right;
			nYpix = clientRect.bottom;

			if (bStretchToFit)
			{
				outputRect.top = outputRect.left = 0;
				outputRect.right	= nXpix;
				outputRect.bottom = nYpix;
			}
			else
			{			
				// Calculate the coordinates to center the object
				if (nXpix > ((double) DIBRect.right * CrtScale))
					Orig_X = (int) ((double) nXpix/2 - 
										((double) DIBRect.right * CrtScale)/2);
				else
					Orig_X = 0;
				if (nYpix > ((double) DIBRect.bottom * CrtScale))
					Orig_Y = (int) ((double) nYpix/2 - 
										((double) DIBRect.bottom * CrtScale)/2);
				else
					Orig_Y = 0;

				outputRect.left  	= Orig_X;
  			outputRect.top   	= Orig_Y;
    		outputRect.right 	= (int) ((double) Orig_X +
    												((double) DIBRect.right * CrtScale));
    		outputRect.bottom	= (int) ((double) Orig_Y +
    	 											((double) DIBRect.bottom * CrtScale));				
			}

			SetScrollSizes(MM_TEXT, 
				CSize(outputRect.right - outputRect.left, 
					outputRect.bottom - outputRect.top));		

			GetClientRect(rrect);
			screen.cx = rrect.Width();
			screen.cy = rrect.Height();
		
		}


		if (DIBRect.right > 1024 || DIBRect.bottom > 1024)
		{
			CWaitCursor cursor;	// this will automatically display a wait cursor		
			if (pDoc->m_dib.m_hDrawDib)
			{
				if (pDC->IsPrinting())
					pDoc->m_dib.Draw(pDC, screen, bFitToPage, PrtScale, lOffCenter);
				else
					pDoc->m_dib.Draw(pDC, screen, bStretchToFit, PrtScale, lOffCenter);
			}	
			else
				AfxMessageBox("m_dib.hDrawDib Error");
		}
		else
		{
			if (pDoc->m_dib.m_hDrawDib)
			{
				if (pDC->IsPrinting())
				{
					CWaitCursor cursor;	// this will automatically display a wait cursor		
					pDoc->m_dib.Draw(pDC, screen, bFitToPage, PrtScale, lOffCenter);
				}
				else
					pDoc->m_dib.Draw(pDC, screen, bStretchToFit, PrtScale, lOffCenter);
			}	
			else
				AfxMessageBox("m_dib.hDrawDib Error");
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

		if (!bDraw && bGenesisMode && bTracker)
		{  		
			spt = GetScrollPosition();

			rb_width = rubberBand.right - rubberBand.left;
			rb_height = rubberBand.bottom - rubberBand.top;
			
			// Redraw the tracking rectangle
			// Transform to display coordinates
	 		
			rb_center_x = ((rubberBand.right - rubberBand.left) / 2)
												+ rubberBand.left;
			rb_center_y = ((rubberBand.bottom - rubberBand.top) / 2)
												+ rubberBand.top;

			// calculate the average width & height
	    rb_avg = (((rubberBand.right - rubberBand.left) +
									 (rubberBand.bottom - rubberBand.top)) / 2);
			rb_avg -= 6;
			
			dim_avg = (dim.cx + dim.cy) / 2;

			// Calculate transformed points			
	 		rubberBand.left = pDoc->m_tracker.m_rect.left = rb_center_x - 
	 			(int) (((double) rb_avg * ((double) dim.cx / (double) dim_avg)) / 2);
	 			
	 		rubberBand.right = pDoc->m_tracker.m_rect.right = rb_center_x + 
	 			(int) (((double) rb_avg * ((double) dim.cx / (double) dim_avg)) / 2);

	 		rubberBand.top = pDoc->m_tracker.m_rect.top = rb_center_y - 
	 			(int) (((double) rb_avg * ((double) dim.cy / (double) dim_avg)) / 2);

	 		rubberBand.bottom = pDoc->m_tracker.m_rect.bottom = rb_center_y + 
	 			(int) (((double) rb_avg * ((double) dim.cy / (double) dim_avg)) / 2);

			pDoc->m_tracker.m_rect = rubberBand;

			// Draw new Tracking Rectangle.
			if (rb_avg > 4)
				pDoc->m_tracker.Draw(pDC);
			else
				pDoc->m_tracker.m_rect.SetRectEmpty();	
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

		if (!bDraw && uTimer1 == NULL)
		{
			GetParent()->SetWindowText(pDoc->GetTitle() + " - " +  ActiveTitle);
			if (bTracker && !bStretchToFit && !bDraw)
			{
				bTracker = FALSE;
				pDoc->m_tracker.GetTrueRect(rubberBand);
				pDoc->m_tracker.Draw(pDC);
			
				rb_left 	 	= (double) rubberBand.left 	/ CrtScale;
				rb_top  		= (double) rubberBand.top  	/ CrtScale;
				rb_right  	= (double) rubberBand.right 	/ CrtScale;
				rb_bottom 	= (double) rubberBand.bottom / CrtScale;

				rubberBand.left 	 = (int) rb_left		+ spt.x;
				rubberBand.top  	 = (int) rb_top			+ spt.y;
				rubberBand.right 	 = (int) rb_right		+ spt.x;
				rubberBand.bottom  = (int) rb_bottom  + spt.y;
																
				// Scale the Screen coordinates
				sxmin = 
					((double ) rubberBand.left / CrtScale - 
					(double ) Orig_X) / ((double ) (dim.cx+1)); 
					//(double ) Orig_X) / ((double ) (dim.cx + 1)); 
				sxmax =
					((double ) rubberBand.right / CrtScale -
					(double ) Orig_X) / ((double ) (dim.cx+1));
					//(double ) Orig_X) / ((double ) (dim.cx + 1));
				symin = 
					((double ) rubberBand.bottom / CrtScale - 
		 			(double ) Orig_Y) / ((double ) (dim.cy+1));
		 			//(double ) Orig_Y) / ((double ) (dim.cy + 1));		
				symax = 
   	 			((double ) rubberBand.top / CrtScale - 
    			(double ) Orig_Y) / ((double ) (dim.cy+1));
    			//(double ) Orig_Y) / ((double ) (dim.cy + 1));

				x_size = CRMAX - CRMIN;
				y_size = CIMAX - CIMIN;

				// Get new fractal coordinates
				CRMIN_NEW = x_size * sxmin + CRMIN;
				CRMAX_NEW = x_size * sxmax + CRMIN;

 				CIMIN_NEW = CIMAX - y_size * symin;
				CIMAX_NEW = CIMAX - y_size * symax;

				CRMID_OLD = CRMID;
				CIMID_OLD = CIMID;
		
				CRMID = ((CRMAX_NEW - CRMIN_NEW) / 2.0) + CRMIN_NEW;
				CIMID	= ((CIMAX_NEW - CIMIN_NEW) / 2.0) + CIMIN_NEW;

				// Calculate the Magnification (2 / average of width & length)
 				dMag_new = ((fabs(CRMAX_NEW - CRMIN_NEW) / 2) 
 										+ (fabs(CIMAX_NEW - CIMIN_NEW) / 2)) / 2;
				if (dMag_new) 
					dMag_new = (1 / dMag_new) * 2;
 			   				
				if (!pDC->IsPrinting())   // if not printer DC
					sprintf(cstr, 
						"Center_R=%f, Center_I=%f, L=%f, T=%f, R=%f, B=%f, Mn=%f",
							CRMID, CIMID, CRMIN_NEW, CIMAX_NEW, CRMAX_NEW, CIMIN_NEW, dMag_new);

				// Draw an X inside the Rubber Band
				CPen penBlackDash(PS_DOT, 0, (COLORREF) 0);
				CPen *ppenDefault = pDC->SelectObject(&penBlackDash);

				pDC->MoveTo(rubberBand.left, rubberBand.top);
				pDC->LineTo(rubberBand.right, rubberBand.bottom);
				pDC->MoveTo(rubberBand.right, rubberBand.top);
				pDC->LineTo(rubberBand.left, rubberBand.bottom);
		  
				pDC->SelectObject(ppenDefault);		
			}	
			else
			{
				// Calculate the Magnification (2 / average of width & length)
 				//dMagnification = ((fabs(CRMAX - CRMIN) / 2) 
 				//						+ (fabs(CIMAX - CIMIN) / 2)) / 2;
				//if (dMagnification) 
					//dMagnification = (1 / dMagnification) * 2;

				if (!pDC->IsPrinting())   // if not printer DC
					sprintf(cstr, 
						"Center_R=%f, Center_I=%f, L=%f, T=%f, R=%f, B=%f, M=%f",
							CRMID, CIMID, CRMIN, CIMAX, CRMAX, CIMIN, dMagnification);		
			}
			
			if (!pDC->IsPrinting())   // if not printer DC
				Status_Bar(cstr);

			if (m_pGradView->GetSafeHwnd() != 0)
			{
				m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
				m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
				m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

				m_pGradView->SetDlgItemInt(IDC_INC_RED, nRed);
				m_pGradView->SetDlgItemInt(IDC_INC_GREEN, nGrn);
				m_pGradView->SetDlgItemInt(IDC_INC_BLUE, nBlu);

				m_pGradView->SetDlgItemInt(IDC_MIN, min);
				m_pGradView->SetDlgItemInt(IDC_MAX, max);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFlarium24View printing

void CFlarium24View::OnFilePrintscaling() 
{
	//char cstr[133];
	
	bPrtParameters_are_set = TRUE;

	CPrtScale pf;
	if (PrtScale == 1) PrtScale = 0;
	if (PrtScale) 
		pf.m_PrintFactor = (int) (PrtScale * 100 - 100);
	
	pf.m_Fit_To_Page = bFitToPage;
	
  if (pf.DoModal() == IDOK) 
	{
    PrtScale = (pf.m_PrintFactor + 100) / 100.0;
		bFitToPage = pf.m_Fit_To_Page;
	}
	else
		bPrtParameters_are_set = FALSE;	
}

BOOL CFlarium24View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFlarium24View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFlarium24View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFlarium24View diagnostics

#ifdef _DEBUG
void CFlarium24View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFlarium24View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFlarium24Doc* CFlarium24View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlarium24Doc)));
	return (CFlarium24Doc*)m_pDocument;
}
#endif //_DEBUG

void CFlarium24View::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
        SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());	
	CFlarium24Doc* pDoc = GetDocument();

	if (bNewView && bZoomingMode)
	{
    if ( ! outFile.Open( szTempFileName, CFile::modeRead ))
    {
      bZoomingMode = FALSE;
      AfxMessageBox ( "Error, Opening File:" + szTempFileName );
			outFile.Close();
			return;
    }
    else
    {
			// Read the parameters from the ASCII file
			Loadparameters();

			// Look for the two common sizes
			if ((nImageSize == 0 && dim.cx == 160 && dim.cy == 120))
			{
				// Do Nothing
			}
			else
			if ((nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
			{
				// Do Nothing
			}
			else
				nImageSize = 10; // Set to custom size

			// Create a new DIB
			if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
			{
				AfxMessageBox("Error Creating DIB");
			}

			GetParentFrame()->SetWindowPos(NULL, 0, 0, dim.cx+40, dim.cy+60,
				SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);

			///////////////////////////////////
			//AfxMessageBox("Step 1");
			bDraw = TRUE;
			bLaunch = FALSE;
		}
		outFile.Close();

		//if (bAutoTile)
	    //AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_WINDOW_TILE_HORZ);
	}

	else if (pDoc->doc_PathName == "")
	{
		// Initial size of new bitmap
		pDoc->m_sizeDoc.cx = global_width;
		pDoc->m_sizeDoc.cy = global_height;

		dim = pDoc->m_sizeDoc;

		if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		{
			AfxMessageBox("Error Creating DIB");
		}

		dim = pDoc->GetDocSize();

    if (outFile.Open( szFluFileName, CFile::modeRead ))	
		{
			Loadparameters();
			outFile.Close();

			szTemp = szTempFileName;
			szTemp.GetBufferSetLength(szTempFileName.GetLength()-3);
			szTemp += "bmp";
			
			if (!pDoc->OnOpenDocument(szTemp))
			{
				bDraw = TRUE;
				bLaunch = FALSE;
			}
			else
			{
		    //OnWindowSizedesktop();
				dim = pDoc->GetDocSize();
				bInitialized = FALSE;
			}
		}
		else
		{
			////////////////////////////////////////////////////////////
			
			// Open the default color file
			if ( ! outFile.Open( szColorFileName, CFile::modeRead ))
			{
				// Create the initial color file
				szTemp = "Flarium.clr";

				// File "Save As" Routine

				if ( ! outFile.Open( szTemp, 
     							CFile::modeWrite | CFile::modeCreate))
				{
					AfxMessageBox ( "Error, Creating File:" + szTemp );
					return;
				}	

				szColorFileName = outFile.GetFilePath();

				// Write the Colours out to an ASCII file
			
				// Write nRedStart
				sprintf(cstr,"%d", nRedStart);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nGrnStart
				sprintf(cstr,"%d", nGrnStart);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nBluStart
				sprintf(cstr,"%d", nBluStart);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nRed
				sprintf(cstr,"%d", nRed);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nGrn
				sprintf(cstr,"%d", nGrn);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nBlu
				sprintf(cstr,"%d", nBlu);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			
		
				outFile.Close();

				AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_DRAW_1);		
			
				GetParentFrame()->SetWindowPos(NULL, 0, 0, dim.cx+40, dim.cy+60,
					SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);
				
				Invalidate();		
				return;
			}

			// Read nRedStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRedStart);

			// Read nGrnStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrnStart);

			// Read nBluStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBluStart);

			// Read nRed
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRed);

			// Read nGrn
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrn);

			// Read nBlu
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBlu);

			outFile.Close();
			
			//////////////////////////////////////////////////////////			
			
			AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_DRAW_1);		
			//OnViewBackground();
			//AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_PALETTE_SCALED);		
			
		}

		GetParentFrame()->SetWindowPos(NULL, 0, 0, dim.cx+40, dim.cy+60,
			SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);

		//outFile.Close();

		//if (!(nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
		//	nImageSize = 10; // Set to custom size

		// Look for the two common sizes
		if ((nImageSize == 0 && dim.cx == 160 && dim.cy == 120))
		{
			// Do Nothing
		}
		else
		if ((nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
		{
			// Do Nothing
		}
		else
			nImageSize = 10; // Set to custom size
		
	}
	else
	{
		// Opening Bitmap from file

    OnWindowSizedesktop();

		// Open the equivalent parameters file, if one exists
		CString szTemp;

		szTemp = pDoc->doc_PathName;
		szTemp = szTemp.GetBufferSetLength(szTemp.GetLength()-3);
		szTemp += "flu";
    
		if ( outFile.Open( szTemp, CFile::modeRead ))
    {
			// Read the parameters from the ASCII file
			Loadparameters();			
			outFile.Close();

			//bDraw = TRUE;
			//bLaunch = FALSE; // Redraw to initialize the temp buffers.
			bInitialized = FALSE;		
		}
	}

	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());	
	bZoomingMode = FALSE;

	// Create Color Table Array
	//ColorTable = new DWORD [dim.cx*dim.cy];		            

  // Copy colors to the ColorTable array
	//if (!::CopyBit(pDoc->hdib, pDoc->m_sizeDoc,
	//	    px, py, (DWORD)RGB(red, grn, blu)))

  Invalidate();		
}

void CFlarium24View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  switch (lHint)
	{
		case ID_APPLICATION_IDLE:
			if (!bDraw && uTimer1)
				Shift_Step();	
			else
				DrawPattern();
			break;

    default:
      break;
  }	
}

void CFlarium24View::Window_Pane(int nStat)
{
  ////////////////////////////////////////////////////////////////////
  // Output something to the Window Caption Bar
	//
	char cstr[81];
	wsprintf(cstr, "%d",nStat);
	GetParent()->SetWindowText(cstr);
}

void CFlarium24View::Status_Bar(char* bar_txt)
{
  ////////////////////////////////////////////////////////////////////
  // Output something to the status bar
	//
 	CStatusBar* pStatus = (CStatusBar*)
   	AfxGetApp()->m_pMainWnd->GetDlgItem(AFX_IDW_STATUS_BAR);
  if (pStatus) 
  {
  	pStatus->SetPaneText(0, bar_txt);
  }
}

void CFlarium24View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Get Pointer to Document
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
	//rubberBand.left = point.x;
  //rubberBand.top  = point.y;
  
	// If clicked inside, drag or resize it. Otherwise create a 
	// rubber band rectangle
	BOOL bResult = pDoc->m_tracker.HitTest(point) != CRectTracker::hitNothing;

	// Tracker rectangle changed so update views.
  if (bResult)
		pDoc->m_tracker.Track(this, point, TRUE);
	else
		 pDoc->m_tracker.TrackRubberBand(this, point, TRUE);

	// pDoc->SetModifiedFlag();

	pDoc->m_tracker.GetTrueRect(rubberBand);

	if (rubberBand.right - rubberBand.left > 10 && 
			rubberBand.bottom - rubberBand.top > 10)
  {
		if (CrtScale == 1) 
			bTracker = TRUE;
		else
			bTracker = FALSE;
  }
  
	pDoc->UpdateAllViews(NULL);  

	if (rsave.left		< Orig_X ||
			rsave.right		> Orig_X + dim.cx ||
			rsave.bottom	> Orig_Y + dim.cy ||
			rsave.top			< Orig_Y)
		Invalidate(TRUE);  	
	else
		Invalidate(FALSE);  	

	rsave.left		= rubberBand.left;
	rsave.right		= rubberBand.right;
	rsave.bottom	= rubberBand.bottom;
	rsave.top			= rubberBand.top;
		
	//bBDown = TRUE;
	//bTracker = TRUE;
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CFlarium24View::OnMouseMove(UINT nFlags, CPoint point) 
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
	// If moving inside the rectangle, drag or resize it. Otherwise
	// show a Cross-hair Cursor
	BOOL bResult = pDoc->m_tracker.HitTest(point) != CRectTracker::hitNothing;

	// Tracker rectangle changed so update views.
  if (bResult)
		::SetCursor(mHSize);
	else
		::SetCursor(mHCross);
	
	CScrollView::OnMouseMove(nFlags, point);
}

//void CFlarium24View::OnRButtonDown(UINT nFlags, CPoint point) 
//{
//	Clearselection(TRUE);	
//	CScrollView::OnRButtonDown(nFlags, point);
//}

void CFlarium24View::Clearselection(BOOL bValid)
{
	// Get Pointer to Document
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRMIN_NEW = 0;
	CIMIN_NEW = 0;
	CRMAX_NEW = 0;
	CIMAX_NEW = 0;

	CRMID = ((CRMAX - CRMIN) / 2.0) + CRMIN;
	CIMID	= ((CIMAX - CIMIN) / 2.0) + CIMIN;

	pDoc->m_tracker.m_rect.SetRectEmpty();	
	bTracker = FALSE;
	
	if (!bDraw) Invalidate(bValid);
}

void CFlarium24View::OnImageSize() 
{
	CFlarium24Doc* pDoc = GetDocument();
	XYSize px;
	dim = pDoc->m_sizeDoc;

	px.m_ImageSize = nImageSize;
	px.m_X_Custom = dim.cx;
	px.m_Y_Custom = dim.cy;
	if (px.DoModal() == IDOK)
	{		
		nImageSize = px.m_ImageSize;
	  switch (nImageSize)
  	{
  		case 0:
  			dim.cx = 160;
  			dim.cy = 120;
  			break;
  		case 1:
  			dim.cx = 256;
  			dim.cy = 256;
  			break;
  		case 2:
	 			dim.cx = 320;
  			dim.cy = 240;
  			break;
  		case 3:
  			dim.cx = 640;
  			dim.cy = 480;
  			break;
  		case 4:
  			dim.cx = 800;
  			dim.cy = 600;
  			break;
  		case 5:
  			dim.cx = 1024;    //
  			dim.cy =  768;    //
  			break;
  		case 6:
  			dim.cx = 1280;    //
  			dim.cy = 1024;    //
  			break;
  		case 7:
  			dim.cx = 1920;    // 
  			dim.cy = 1440;    // 
  			break;
  		case 8:
  			dim.cx = 2400;    // 
  			dim.cy = 1800;    // 
  			break;
  		case 9:
				dim.cx = 3564;
				dim.cy = 2784;

  			break;

	  	case 10:
  			//	dim.cx = 3072;    // This size gets a creation error
  		 	//	dim.cy = 2304;    // 

				// Get custom sizes
				dim.cx = px.m_X_Custom & 0x7FFE; // Make even bitmap sizes
				dim.cy = px.m_Y_Custom & 0x7FFE;
					
				break;

  		default:
  			AfxMessageBox("Shouldn't Get Here - OnImageSize");
				return;
  	}
		
		global_width = dim.cx;
		global_height = dim.cy;

		pDoc->m_sizeDoc	= dim;

		// Create a new DIB
		if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		{
			AfxMessageBox("Error Creating DIB");
		}
		
		OnWindowSizedesktop();

    //if (nDistortion == (-1))
  		//OnViewBackground();

    pDoc->bMerge = FALSE;
    if (nDistortion >= 0)
    {
      bDraw = TRUE;
		  bLaunch = FALSE;
    }
	}
}

void CFlarium24View::OnWindowSizedesktop() 
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int ccx, ccy;

	dim = pDoc->m_dib.GetSize();

	//dim = pDoc->GetDocSize();

	CRect rParentArea;
	GetActiveWindow()->GetWindowRect(rParentArea);

 	ccx = rParentArea.right - rParentArea.left - 20;
 	ccy = rParentArea.bottom - rParentArea.top - 45;

	//char cstr[81];
	//wsprintf(cstr,"top=%d, left=%d, ccx=%d,  ccy=%d",
	//	rParentArea.top, rParentArea.left, ccx, ccy);
	//AfxMessageBox(cstr);	

	if (dim.cx + 40 > ccx)
		ccx = ccx - 100;
	else
		ccx = dim.cx;

	if (dim.cy + 60 > ccy)
		ccy = ccy - 150;
	else
		ccy = dim.cy;

	GetParentFrame()->SetWindowPos(NULL, 0, 0, ccx+40, ccy+60,
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);
		//SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());	
}

void CFlarium24View::OnViewZoom() 
{
	// Get Pointer to Document
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  pDoc->m_tracker.m_rect.SetRectEmpty();	
		
	if (CRMIN_NEW < CRMAX_NEW &&
			CIMIN_NEW < CIMAX_NEW)
	{		
		bZoomingMode = TRUE;

		CRMIN_OLD = CRMIN;
		CIMIN_OLD = CIMIN;
		CRMAX_OLD = CRMAX;
		CIMAX_OLD = CIMAX;
			
		CRMIN = CRMIN_NEW;
		CIMIN = CIMIN_NEW;
		CRMAX = CRMAX_NEW;
		CIMAX = CIMAX_NEW;
		
		CRMIN_JUL = CRMIN_NEW;
		CIMIN_JUL = CIMIN_NEW;
		CRMAX_JUL = CRMAX_NEW;
		CIMAX_JUL = CIMAX_NEW;

		CRMIN_NEW = 0;
		CIMIN_NEW = 0;
		CRMAX_NEW = 0;
		CIMAX_NEW = 0;

		//////////////////////////////////////////
		if (bNewView)
		{
			// Create new view and return			
			ViewNew();
			OnEditUndofractalselection();
			return;
		}	
		else
		{
			if (jul == 0 || jul_save == 1)
			{
				rx_ratio = (double) dim.cx/(double) (dim.cy);
				ry_ratio = (double) dim.cy/(double) (dim.cx);

				rx_ratio = rx_ratio + (1-rx_ratio)/2;
				ry_ratio = ry_ratio + (1-ry_ratio)/2;

				// Calculate the Magnification (2 / average of width & length)
 				dMagnification = ((fabs((CRMAX - CRMIN)/rx_ratio) / 2) 
 							+ (fabs((CIMAX - CIMIN)/ry_ratio) / 2)) / 2;
				if (dMagnification) 
					dMagnification = (1 / dMagnification) * 2;

			}			
			//OnViewBackground();
			bDraw = TRUE;			
			bLaunch = FALSE;
		}
 	}
}

void CFlarium24View::OnUpdateViewZoom(CCmdUI* pCmdUI) 
{
	if (CRMIN_NEW < CRMAX_NEW &&
			CIMIN_NEW < CIMAX_NEW)
	{		
		pCmdUI->Enable(TRUE);	
	}	
	else
		pCmdUI->Enable(FALSE);	
}

void CFlarium24View::OnViewNew() 
{
	bNewView ^= 1;
}

void CFlarium24View::OnUpdateViewNew(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bNewView);	
}

void CFlarium24View::ViewNew() 
{	
  if (!outFile.Open( szTempFileName, 
     		CFile::modeWrite | CFile::modeCreate))
  {
    AfxMessageBox ( "Error, Opening File:" + szTempFileName );
		outFile.Close();
		return;
	}	
	else
	{
		// Write the parameters out to an ASCII file
		Saveparameters();                                    
	}
	outFile.Close();

	// Close the Gradient window to avoid confusion if one is open
	if (m_pGradView->GetSafeHwnd())
		m_pGradView->DestroyWindow();	
	
	// Close the Affine window to avoid confusion if one is open
	if (m_pAffineView->GetSafeHwnd())
		m_pAffineView->DestroyWindow();	

	GetParent()->SendMessage(WM_COMMAND, ID_FILE_NEW);	
}

void CFlarium24View::OnSaveDib() 
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Save Parameters File
	szTemp =
	//szTempFileName =
		pDoc->doc_PathName.GetBufferSetLength(pDoc->doc_PathName.GetLength()-3);
	//szTempFileName = szTempFileName + "flu";
	szTemp = szTemp + "flu";

	// Write the parameters out to an ASCII file
	if (!outFile.Open( szTemp, 
     		CFile::modeWrite | CFile::modeCreate))
  {
    AfxMessageBox ( "Error, Opening File:" + szTemp );
		return;
	}	
	else
	{
		// Write the parameters out to an ASCII file
		Saveparameters();                                    
	}
	outFile.Close();

}

void CFlarium24View::OnFileSavecolors() 
{
  szTemp = "Flarium.clr";

	// File "Save As" Routine

	CFileDialog dlg
	    (FALSE,
	   	"clr",
	   	szTemp,          
	    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	    "Flarium Colors (*.clr)|*.clr|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              
    if ( ! outFile.Open( szTemp, 
     							CFile::modeWrite | CFile::modeCreate))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
		}	
		else
		{
			// Write the parameters out to an ASCII file
			
			// Write nRedStart
			sprintf(cstr,"%d", nRedStart);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nGrnStart
			sprintf(cstr,"%d", nGrnStart);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nBluStart
			sprintf(cstr,"%d", nBluStart);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nRed
			sprintf(cstr,"%d", nRed);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nGrn
			sprintf(cstr,"%d", nGrn);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nBlu
			sprintf(cstr,"%d", nBlu);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			
		
		}
		outFile.Close();
	}
}

void CFlarium24View::OnFileSaveparameters() 
{
	//char cstr[81];
	//CString szTemp;

	// Get The Current Time To be Used with the filename		
	//dwFileTime = GetTickCount() + dwDeltaTime ; 
	//MilliTime(dwFileTime) ;  						
	//sprintf(cstr, "%03s%c%02ld%02ld.flu", 
		//szGradient,(char)dwHrs+'a',dwMin,dwSec);
	//szTemp = cstr;

  szTemp = "Flarium.flu";

	// File "Save As" Routine

	CFileDialog dlg
	    (FALSE,
	   	"flu",
	   	szTemp,          
	    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	    "Fractal Parameters (*.flu)|*.flu|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              
    if ( ! outFile.Open( szTemp, 
     							CFile::modeWrite | CFile::modeCreate))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
		}	
		else
		{
			// Write the parameters out to an ASCII file
			Saveparameters();                                    
		}
		outFile.Close();
	}
}

void CFlarium24View::Saveparameters() 
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	global_width	= dim.cx;
	global_height = dim.cy;
	
	// Write the parameters out to an ASCII file

	outFile.WriteString(ActiveTitle + '\n');			

	// Write the fractal type
	sprintf(cstr,"%d", nDistortion);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the filter type
	sprintf(cstr,"%d", nFilter);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

//////////////////////////////////////////////
	// Write the bInvertFractal BOOL variable
	sprintf(cstr,"%d", bInvertFractal);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

  // Write bZeroInit BOOL Variable
	sprintf(cstr,"%d", bZeroInit);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');  

///////////////////////////////////////////////
	// Write the 'jul' variable
	sprintf(cstr,"%d", jul);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the 'jul_save' variable
	sprintf(cstr,"%d", jul_save);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the 'rn" variable
	sprintf(cstr,"%.16Lg", rn);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the maximum iterations
	sprintf(cstr,"%d", NMAX);			// max iterations
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nRedStart Variable
	sprintf(cstr,"%d", nRedStart);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nGrnStart Variable
	sprintf(cstr,"%d", nGrnStart);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nBluStart Variable
	sprintf(cstr,"%d", nBluStart);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nRed Variable
	sprintf(cstr,"%d", nRed);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nGrn Variable
	sprintf(cstr,"%d", nGrn);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nBluStart Variable
	sprintf(cstr,"%d", nBlu);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the min variable
	sprintf(cstr,"%d", min);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the max Variable
	sprintf(cstr,"%d", max);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nFF Variable
	sprintf(cstr,"%d", nFF);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nColorMethod Variable
	sprintf(cstr,"%d", nColorMethod);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
///////////////////////////////////////////////////////
	sprintf(cstr,"%f", nBay100);	// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%f", nBay1000);	// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
	
	sprintf(cstr,"%f", (double)dBiomorph);	// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%f", (double) dBailout);		// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%f", dStrands);		// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMIN);		// x left
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMIN);    // y top
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMAX);    // x right
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMAX);    // y bottom
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMIN_JUL);		// x left
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMIN_JUL);    // y top
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMAX_JUL);    // x right
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMAX_JUL);    // y bottom
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMID);    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMID);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cx);    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cy);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", rorder_r);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", rorder_i);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

///////////////////////////////////////////////////	
	sprintf(cstr,"%.16Lg", cn.real());    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cn.imag());    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cr.real());    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cr.imag());    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the 'cOrient.real()' variable
	sprintf(cstr,"%.16Lg", cOrient.real());
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the 'cOrient.imag()' variable
	sprintf(cstr,"%.16Lg", cOrient.imag());
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the 'dMIN' variable
	sprintf(cstr,"%.16Lg", dMIN);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the Fractal Dimension type
	sprintf(cstr,"%d", nFDOption);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bMFilter BOOL variable
	sprintf(cstr,"%d", bMFilter);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bMSet BOOL variable
	sprintf(cstr,"%d", bMSet);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bFSet BOOL variable
	sprintf(cstr,"%d", bFSet);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	////////////////////////////////////

	sprintf(cstr,"%.16Lg", dCloud_top);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", dCloud_bottom);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", dCloud_left);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", dCloud_right);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	////////////////////////////////////////
	// Save the Latoocarfian variables

	sprintf(cstr,"%.16Lg", mx);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", my);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", ma);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", mb);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", mc);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", md);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	///////////////////////////////////
	// Save the Affine Transformation variables

	sprintf(cstr,"%.16Lg", af[1]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[2]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[3]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[4]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[5]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[6]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[7]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[8]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[9]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[10]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[11]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[12]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[13]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[14]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[15]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[16]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[17]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[18]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[19]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[20]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[21]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[22]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[23]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[24]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[25]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[26]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[27]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[28]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[29]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", af[30]);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	////////////////////////////
	// Save the background colors

	sprintf(cstr,"%d", nRedBack);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%d", nGrnBack);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%d", nBluBack);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the Attractors count
	sprintf(cstr,"%d", latoof_count);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the nDimension variable
	sprintf(cstr,"%d", nDimension);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	//////////////
	// Quaternion constants
	//
	// qk1 = .01;
	// qk2 = .01;
	// qt1 = 0;
	// qt2 = 0;

	sprintf(cstr,"%.16Lg", qk1);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", qk2);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", qt1);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", qt2);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

  ////////////////////////////////////////
  // Parser Variables
	sprintf(cstr,"%.16Lg", u_real);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", u_imag);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", v_real);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", v_imag);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", w_real);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", w_imag);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	outFile.WriteString(strFormulae + '\n');			
	
	////////////////////////////////////////////
  // Write the bFDVariate BOOL Variable
	sprintf(cstr,"%d", bFDVariate);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');  

  // Write the bNothingButStrands BOOL Variable
	sprintf(cstr,"%d", bNothingButStrands);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');  

  // Write the bGenesisMode BOOL Variable
	sprintf(cstr,"%d", bGenesisMode);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');  

	// Write the nColorOrder Variable
	sprintf(cstr,"%d", nColorOrder);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

}

void CFlarium24View::OnFileLoadcolors() 
{
	CString szTemp;

	// File "Load From Parameters" Routine

	CFileDialog dlg
	    (TRUE,
	   	"*.clr",
	   	szTemp,          
	     OFN_HIDEREADONLY,
	    "Fractal Parameters (*.clr)|*.clr|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              

    if ( ! outFile.Open( szTemp, CFile::modeRead ))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
    }
    else
    {
			// Read the parameters from the ASCII file

			// Read nRedStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRedStart);

			// Read nGrnStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrnStart);

			// Read nBluStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBluStart);

			// Read nRed
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRed);
		
			// Read nGrn
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrn);
		
			// Read nBlu
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBlu);
				
		}
		outFile.Close();

		//PostMessage(WM_DLGGRADIENT, ID_APPLY);

		bDraw = TRUE;
		bLaunch = FALSE;
		//bColorChange = TRUE;

		if (m_pGradView->GetSafeHwnd() != 0)
		{		
			m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
			m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
			m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

			m_pGradView->SetDlgItemInt(IDC_INC_RED, nRed);
			m_pGradView->SetDlgItemInt(IDC_INC_GREEN, nGrn);
			m_pGradView->SetDlgItemInt(IDC_INC_BLUE, nBlu);

			m_pGradView->ScrollBarInit();

			if (bForward)
				m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
			else
				m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

			m_pGradView->UpdateData(TRUE);
			m_pGradView->ScrollBarInit();

		}
	}
}

void CFlarium24View::OnFileLoadparameters() 
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString szTemp;

	// File "Load From Parameters" Routine

	CFileDialog dlg
	    (TRUE,
	   	"*.flu",
	   	szTemp,          
	     OFN_HIDEREADONLY,
	    "Fractal Parameters (*.flu)|*.flu|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              

    if ( ! outFile.Open( szTemp, CFile::modeRead ))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
    }
    else
    {
			// Read the parameters from the ASCII file
			Loadparameters();
			if (!(nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
				nImageSize = 10; // Set to custom size
		}
		outFile.Close();

		szTemp.GetBufferSetLength(szTemp.GetLength()-3);
		szTemp += "bmp";
		
		pDoc->doc_PathName = szTemp;
		pDoc->SetTitle(szTemp);
		pDoc->SetPathName(szTemp);

		if (nDistortion)
		{
			//sprintf(cstr,"CRMID=%f,CIMID=%f",CRMID,CIMID);
			//szTemp = cstr;
			//AfxMessageBox(ActiveTitle + ": " + szTemp);

			bDraw = TRUE;
			bLaunch = FALSE;
		}	
	}
}

void CFlarium24View::Loadparameters() 
{
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// Read the parameters from the ASCII file

	if (outFile.ReadString ( ctitle, (sizeof(cstr)-1)) == NULL)
	{
		AfxMessageBox("Error Reading from Parameter File:" + szTemp);
    return;
  }
      	
	ActiveTitle = ctitle;
	pDoc->doc_PathName = ActiveTitle;

	// Search for the Line Feed loacation 
	int iLFLoc = ActiveTitle.ReverseFind('\n');
	// Replace the Line Feed character with NULL for viewing
	if (iLFLoc >= 0) 
	ActiveTitle.GetBufferSetLength(ActiveTitle.GetLength()-1); 

	// Read fractal type
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nDistortion);

	// Read filter type
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nFilter);

	// Read bInvertFractal BOOL variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bInvertFractal);

	// Read bZeroInit BOOL Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bZeroInit);
			
	// Read the 'jul' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &jul);

	// Read the 'jul_save' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &jul_save);

	// Read the 'rn' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  rn = (double) atof(cstr);							// 

	// Read maximum iterations
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &NMAX);     // max iterations
			
	// Read nRedStart
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nRedStart);   

	// Read nGrnStart
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nGrnStart);   

	// Read nBluStart
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nBluStart);   

	// Read nRed
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nRed);   

	// Read nGrn
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nGrn);   

	// Read nBlu
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nBlu);   

	// Read min
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &min);   

	// Read max
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &max);   

	// Read nFF
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nFF);   

	// Read nColorMethod
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nColorMethod);   

//////////////////////////////////////////////////
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  nBay100 = atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  nBay1000 = atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dBiomorph = (int) atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dBailout = (int) atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dStrands = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMIN = atof(cstr);							// x left

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMIN = atof(cstr);							// y top

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMAX = atof(cstr);							// x right

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMAX = atof(cstr);							// y bottom

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMIN_JUL = atof(cstr);							// x left

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMIN_JUL = atof(cstr);							// y top

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMAX_JUL = atof(cstr);							// x right

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMAX_JUL = atof(cstr);							// y bottom
  
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMID = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMID = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cx = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cy = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  rorder_r = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
 	rorder_i = atof(cstr);							//

///////////////////////////////////////////////////////
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	cn.set_real(atof(cstr));

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	cn.set_imag(atof(cstr));

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	cr.set_real(atof(cstr));

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	cr.set_imag(atof(cstr));

	// Read the 'cOrient.real()' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cOrient.set_real((double) atof(cstr));							// 

	// Read the 'cOrient.imag()' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cOrient.set_imag((double) atof(cstr));							// 

	// Read the 'dMIN' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dMIN = atof(cstr);							// 

	// Read Fractal Dimension type
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nFDOption);

	// Read bMFilter BOOL variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bMFilter);

	// Read bMSet BOOL variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bMSet);

	// Read bFSet BOOL variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bFSet);

////////////////////////////////////

	// Read the 'dCloud_top' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dCloud_top = atof(cstr);							// 

	// Read the 'dCloud_bottom' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dCloud_bottom = atof(cstr);							// 

	// Read the 'dCloud_left' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dCloud_left = atof(cstr);							// 

	// Read the 'dCloud_right' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dCloud_right = atof(cstr);							// 

	if (dCloud_top == 0 &&
			dCloud_bottom == 0 &&
			dCloud_left == 0 &&
			dCloud_right == 0)
	{
		dCloud_top		= 2;
		dCloud_bottom	= -2;
		dCloud_left		= -2;	
		dCloud_right	= 2;			
	}

	if (jul == 1)
	{
		CRMID = ((CRMAX_JUL - CRMIN_JUL) / 2.0) + CRMIN_JUL;
    CIMID	= ((CIMAX_JUL - CIMIN_JUL) / 2.0) + CIMIN_JUL;

    if (bJuliaMode)
    {
			CRMIN_JUL  	= -2.0;	//	-2.0;		// left
			CIMIN_JUL  	= -2.0;	//	-1.2;   // top
			CRMAX_JUL  	=  2.0;	//	1.0;    // right
			CIMAX_JUL  	=  2.0;	//	1.2;    // bottom
			bJuliaMode = FALSE;
		}	
	}

	//////////////////////////////////////////
	// Read the Latoocarfian variables
	
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  mx = atof(cstr);							// 

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  my = atof(cstr);							// 

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  ma = atof(cstr);							// 

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  mb = atof(cstr);							// 

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  mc = atof(cstr);							// 

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  md = atof(cstr);							// 

	////////////////////////////////////
	// Read the Affine Transformation Variable

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[1] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[2] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[3] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[4] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[5] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[6] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[7] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[8] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[9] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[10] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[11] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[12] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[13] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[14] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[15] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[16] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[17] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[18] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[19] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[20] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[21] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[22] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[23] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[24] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[25] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[26] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[27] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[28] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[29] = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  af[30] = atof(cstr);

	/////////////////////////////////
	// Read the background colors

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nRedBack);

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nGrnBack);

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nBluBack);

	// Read Latoof count
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &latoof_count);

	if (latoof_count < 1) 
		latoof_count = 10000;

	nDimension = 0;

	// Read the nDimension variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nDimension);

	if (nDimension < 0 || nDimension > 2)
		nDimension = 0;

	//////////////
	// Quaternion constants
	//
	// qk1 = .01;
	// qk2 = .01;
	// qt1 = 0;
	// qt2 = 0;

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  qk1 = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  qk2 = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  qt1 = atof(cstr);

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  qt2 = atof(cstr);	
	
  ///////////////////////////////////
  // Parser Variables
	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  u_real = atof(cstr);	

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  u_imag = atof(cstr);	
  
	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  v_real = atof(cstr);	

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  v_imag = atof(cstr);	
  
	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  w_real = atof(cstr);	

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  w_imag = atof(cstr);	

  uu.set_real(u_real);
  uu.set_imag(u_imag);

  vv.set_real(v_real);
  vv.set_imag(v_imag);

  ww.set_real(w_real);
  ww.set_imag(w_imag);  

	if (outFile.ReadString ( cstr, (sizeof(cstr)-1)) == NULL)
	{
		//AfxMessageBox("Error Reading from Parameter File:" + szTemp);
    //return;
    wsprintf(cstr,"z*z+c");
  }
      	
	strFormulae = cstr;

	// Search for the Line Feed loacation 
	iLFLoc = strFormulae.ReverseFind('\n');
	// Replace the Line Feed character with NULL for viewing
	if (iLFLoc >= 0) 
	  strFormulae.GetBufferSetLength(strFormulae.GetLength()-1);   

  int i_try = 0;      
  ParsedExpr = ParseExpression( strFormulae, i_try );

  /////////////////////////////////////////
	
	pDoc->m_sizeDoc = dim;
	///////////////////////////////////////////

	// Read the bFDVariate BOOL Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bFDVariate);			

	// Read the bNothingButStrands BOOL variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bNothingButStrands);			

	// Read the bGenesisMode BOOL Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bGenesisMode);			

	// Read nColorOrder
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nColorOrder);   
	
	if (jul == 0 || jul_save == 1)
	{
	  rx_ratio = (double) dim.cx/(double) (dim.cy);
	  ry_ratio = (double) dim.cy/(double) (dim.cx);

	  rx_ratio = rx_ratio + (1-rx_ratio)/2;
	  ry_ratio = ry_ratio + (1-ry_ratio)/2;

	  // Calculate the Magnification (2 / average of width & length)
 	  dMagnification = ((fabs((CRMAX - CRMIN)/rx_ratio) / 2) 
 							+ (fabs((CIMAX - CIMIN)/ry_ratio) / 2)) / 2;
	  if (dMagnification) 
		  dMagnification = (1 / dMagnification) * 2;
	}

}

void CFlarium24View::OnEditUndofractalselection() 
{
	if (CRMIN_OLD < CRMAX_OLD &&
			CIMIN_OLD < CIMAX_OLD)
	{		
		CRMIN = CRMIN_OLD;
		CIMIN = CIMIN_OLD;
		CRMAX = CRMAX_OLD;
		CIMAX = CIMAX_OLD;
		
		CRMID = CRMID_OLD;
		CIMID = CIMID_OLD;
		
		CRMIN_JUL = CRMIN_OLD;
		CIMIN_JUL = CIMIN_OLD;
		CRMAX_JUL = CRMAX_OLD;
		CIMAX_JUL = CIMAX_OLD;

		// Get Pointer to Document
		CFlarium24Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		CRMIN_NEW = 0;
		CIMIN_NEW = 0;
		CRMAX_NEW = 0;
		CIMAX_NEW = 0;

		pDoc->m_tracker.m_rect.SetRectEmpty();	
		
		//bDraw = TRUE;
		//bLaunch = FALSE;
	}
}

void CFlarium24View::OnViewJulia1() 
{
	int jul_t1 = jul;
	int jul_save_t1 = jul_save;

	jul = 1;
	jul_save = 0;

	//////////////////////////////////////////
	if (bNewView)
	{
		// Create new view and return			
		bZoomingMode = TRUE;
		bJuliaMode = TRUE;

		CRMIN_OLD = CRMIN;
		CIMIN_OLD = CIMIN;
		CRMAX_OLD = CRMAX;
		CIMAX_OLD = CIMAX;
			
		CRMIN  	= -1.0;	//		// left
		CIMIN  	= -1.0;	//    // top
		CRMAX  	=  1.0;	//	  // right
		CIMAX  	=  1.0;	//	  // bottom
		
		//CRMIN = CRMIN_NEW;
		//CIMIN = CIMIN_NEW;
		//CRMAX = CRMAX_NEW;
		//CIMAX = CIMAX_NEW;

		//CRMIN = CRMIN_JUL; 
  	//CIMIN = CIMIN_JUL;
  	//CRMAX = CRMAX_JUL;
  	//CIMAX = CIMAX_JUL;

		CRMIN_JUL = CRMIN_NEW;
		CIMIN_JUL = CIMIN_NEW;
		CRMAX_JUL = CRMAX_NEW;
		CIMAX_JUL = CIMAX_NEW;

		CRMIN_NEW = 0;
		CIMIN_NEW = 0;
		CRMAX_NEW = 0;
		CIMAX_NEW = 0;

		ViewNew();
		bZoomingMode = FALSE;
		bJuliaMode = FALSE;

		OnEditUndofractalselection();		// ??

		jul = jul_t1;
		jul_save = jul_save_t1;
		
		return;
	}	
	//else
	//	OnViewBackground();
	
	//////////////////////////////////////////
		
	CRMIN  	= -1.0;	//		// left
	CIMIN  	= -1.0;	//    // top
	CRMAX  	=  1.0;	//	  // right
	CIMAX  	=  1.0;	//	  // bottom

	CRMIN_JUL  	= -1.5;	//		// left
	CIMIN_JUL  	= -1.5;	//    // top
	CRMAX_JUL  	=  1.5;	//	  // right
	CIMAX_JUL  	=  1.5;	//	  // bottom
  
	//nSaveDistortion = nDistortion;

	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_tracker.m_rect.SetRectEmpty();	

	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateViewJulia1(CCmdUI* pCmdUI) 
{
	if (CRMIN_NEW < CRMAX_NEW &&
			CIMIN_NEW < CIMAX_NEW)
	{		
		if (jul == 0)
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}

	if (jul == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CFlarium24View::OnImageParams() 
{
  CFParams fparam;
	//fparam.m_Top 				= (double) CIMAX;
	//fparam.m_Bottom 		= (double) CIMIN;
	//fparam.m_Left   		= (double) CRMIN;
	//fparam.m_Right   		= (double) CRMAX;

	fparam.m_Magnification = dMagnification;
	fparam.m_X_Mid = CRMID;
	fparam.m_Y_Mid = CIMID;

	fparam.m_Iterations	=	NMAX;
	fparam.m_dMIN				=	dMIN;
	fparam.m_Bailout    = (double) dBailout;

	fparam.m_cn_Real    = (double) rorder_r;
	fparam.m_cn_Imag    = (double) rorder_i;

	fparam.m_BayFact1 = (double) nBay100;
	fparam.m_BayFact2 = (double) nBay1000;
	fparam.m_FilterFactor = nFF;
	fparam.m_Strands = dStrands;

	if (jul == 1)
	{
		fparam.m_Julia_X = cx;
		fparam.m_Julia_Y = cy;
	}
	else
	{
		fparam.m_Julia_X = 0;
		fparam.m_Julia_Y = 0;
	}

	if (fparam.DoModal() == IDOK)
	{
		//CIMAX = fparam.m_Top;
		//CIMIN = fparam.m_Bottom;
		//CRMIN = fparam.m_Left;
		//CRMAX = fparam.m_Right;

		//CIMAX_JUL = fparam.m_Top;
		//CIMIN_JUL = fparam.m_Bottom;
		//CRMIN_JUL = fparam.m_Left;
		//CRMAX_JUL = fparam.m_Right;

		dMagnification = fparam.m_Magnification;
		CRMID = fparam.m_X_Mid;
		CIMID = fparam.m_Y_Mid;
				
		NMAX  = JMAX = fparam.m_Iterations;
		dMIN  = fparam.m_dMIN;
		dBailout = (int) fparam.m_Bailout;

		rorder_r = fparam.m_cn_Real;
		rorder_i = fparam.m_cn_Imag;	
		cn.set_real(rorder_r);
		cn.set_imag(rorder_i);

		nBay100  = fparam.m_BayFact1;
		nBay1000 = fparam.m_BayFact2;
		nFF      = fparam.m_FilterFactor;
		dStrands = fparam.m_Strands;

		if (jul == 1)
		{
			cx = fparam.m_Julia_X;
			cy = fparam.m_Julia_Y;
		}
		else
		{
			if (fparam.m_Julia_X || fparam.m_Julia_Y)
			{
				CRMID = cx = fparam.m_Julia_X;
				CIMID = cy = fparam.m_Julia_Y;

				CRMIN_NEW = cx - 1;	//	-2.0;		// left
				CIMIN_NEW = cy - 1;	//	-1.2;   // top
				CRMAX_NEW = cx + 1;	//	1.0;    // right
				CIMAX_NEW = cy + 1;	//	1.2;    // bottom
				
				//jul = 1;
				//jul_save = 0;

				OnViewJulia1();

				return;
			}
			else
			{	
				cx = 0;
				cy = 0;
			}
		}

		bDraw = TRUE;
		bLaunch = FALSE;
	}
}

void CFlarium24View::OnDrawAbort() 
{
	bAbort = TRUE;
}

void CFlarium24View::OnUpdateDrawAbort(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bDraw);
}

void CFlarium24View::OnDrawInvert() 
{
	bInvertFractal ^= 1;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateDrawInvert(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bInvertFractal);
}

long CFlarium24View::OnApply_ShiftView(UINT wParam, LONG lParam)
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return 0L;
	
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (wParam == ID_SHIFTCLOSE)
	{
		bGradient = FALSE;
		m_pGradView->DestroyWindow();
	}	
	else
	{		
		nRed = 
			m_pGradView->GetDlgItemInt(IDC_INC_RED);
		nGrn = 
			m_pGradView->GetDlgItemInt(IDC_INC_GREEN);
		nBlu = 
			m_pGradView->GetDlgItemInt(IDC_INC_BLUE);

		nRedStart = 
			m_pGradView->GetDlgItemInt(IDC_START_RED);
		nGrnStart = 
			m_pGradView->GetDlgItemInt(IDC_START_GREEN);
		nBluStart = 
			m_pGradView->GetDlgItemInt(IDC_START_BLUE);

		if (wParam == ID_SHIFTREVERSE && bForward == TRUE)
		{			
			bRedStart ^= TRUE;
			bGrnStart ^= TRUE;
			bBluStart ^= TRUE;

			for (i=0; i<dim.cx*dim.cy; i++)
			{
				bRed[i] ^= TRUE;
				bGrn[i] ^= TRUE;
				bBlu[i] ^= TRUE;
			}
			bForward = FALSE;
		}
		else
		if (wParam == ID_SHIFTFORWARD && bForward == FALSE)
		{			
			bRedStart ^= TRUE;
			bGrnStart ^= TRUE;
			bBluStart ^= TRUE;

			for (i=0; i<dim.cx*dim.cy; i++)
			{
				bRed[i] ^= TRUE;
				bGrn[i] ^= TRUE;
				bBlu[i] ^= TRUE;
			}
			bForward = TRUE;						
		}		
		
		if (bForward)
			m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
		else
			m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

		UpdateData(TRUE);

		if ( wParam == ID_SHIFTFORWARD || wParam == ID_SHIFTREVERSE )
			Shift_Step();
		else
			Apply_Color();
	}
	return 0L;
}

void CFlarium24View::Apply_Color() 
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return;
	
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
			
	if (nColorMethod > 22)
	{
		bDraw = TRUE;  // ??
		bLaunch = FALSE;
	}
	else
	{
		//if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
			//														nGrnStart, nBluStart, mIter_Data))

		if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
																nGrnStart, nBluStart,
																rIter_Data, gIter_Data, bIter_Data,
																nColorOrder))

			AfxMessageBox("Color shift error");
	}

	if (m_pGradView->GetSafeHwnd() != 0)
	{		
		m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
		m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
		m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);
		m_pGradView->UpdateData(TRUE);
		m_pGradView->ScrollBarInit();
	}

	Invalidate(FALSE);
}

void CFlarium24View::Shift_Step() 
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return;
	
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Apply color shift algorithm
	
	if (bRedStart)
	{
		if (nRedStart + nRed <= 255)
		{			
			nRedStart	+= nRed;
		}
		else
		{						
			nRedStart	-= nRed;
			bRedStart = FALSE;
		}
	}
	else
	{
		if (nRedStart - nRed >= 0)
		{			
			nRedStart -= nRed;
		}
		else
		{			
			nRedStart += nRed;
			bRedStart = TRUE;
		}			
	}
		
	if (bGrnStart)
	{
		if (nGrnStart + nGrn <= 255)
		{			
			nGrnStart	+= nGrn;
		}
		else
		{			
			nGrnStart	-= nGrn;
			bGrnStart = FALSE;
		}
	}
	else
	{
		if (nGrnStart - nGrn >= 0)
		{			
			nGrnStart -= nGrn;
		}
		else
		{			
			nGrnStart += nGrn;
			bGrnStart = TRUE;
		}			
	}

	if (bBluStart)
	{
		if (nBluStart + nBlu <= 255)
		{			
			nBluStart	+= nBlu;
		}
		else
		{			
			nBluStart	-= nBlu;
			bBluStart = FALSE;
		}
	}
	else
	{
		if (nBluStart - nBlu >= 0)
		{			
			nBluStart -= nBlu;
		}
		else
		{			
			nBluStart += nBlu;
			bBluStart = TRUE;
		}			
	}
			
	if (nColorMethod > 22)
	{
		bDraw = TRUE;  // ??
		bLaunch = FALSE;
	}
	else
	{
		//if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
			//														nGrnStart, nBluStart, mIter_Data))

		if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
																nGrnStart, nBluStart,
																rIter_Data, gIter_Data, bIter_Data,
																nColorOrder))

			AfxMessageBox("Color shift error");
	}

	if (m_pGradView->GetSafeHwnd() != 0)
	{		
		m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
		m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
		m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);
		m_pGradView->UpdateData(TRUE);	
		m_pGradView->ScrollBarInit();
	}

	Invalidate(FALSE);
}

void CFlarium24View::OnShiftStart() 
{
//	if (!bDraw && uTimer1 == NULL)
//	{
//	 	if (uTimer1 == NULL)
//			uTimer1 = SetTimer(1, nSpeed, NULL);
//	}
//	else
//	{
//		KillTimer(1);
//		uTimer1 = NULL;
//	}

	if (dim.cx > 1024 || dim.cy > 1024)
		return;

	if (!bDraw && uTimer1 == NULL)
	{
		uTimer1 = 1;
		bGlobalDraw = TRUE;
		m_pGradView->m_Cycle_Button.SetState(TRUE);
	}
	else
	{
		uTimer1 = 0;
		if (!bDraw)
			bGlobalDraw = FALSE;

		if (m_pGradView->GetSafeHwnd() != 0)
		{		
			m_pGradView->m_Cycle_Button.SetState(FALSE);
			m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
			m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
			m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

			if (bForward)
				m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
			else
				m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

			m_pGradView->UpdateData(TRUE);
			m_pGradView->ScrollBarInit();
		}
	}
}

void CFlarium24View::OnUpdateShiftStart(CCmdUI* pCmdUI) 
{
	if (uTimer1 == NULL)
		pCmdUI->SetCheck(FALSE);
	else
		pCmdUI->SetCheck(TRUE);	

	pCmdUI->Enable(bInitialized);
}

void CFlarium24View::OnTimer(UINT nIDEvent) 
{
	if (!bDraw)
	{
		if (nIDEvent == uTimer1)
			Shift_Step();	
	}
	else
	{
		KillTimer(1);
		uTimer1 = NULL;
		Invalidate(FALSE);
	}

	CScrollView::OnTimer(nIDEvent);
}

void CFlarium24View::OnImageColorparameters() 
{	
	if (m_pGradView->GetSafeHwnd() == 0)
	{
		// Create the non-modal dialog
		bGradient = TRUE;

		m_pGradView->Create();

		// m_pGradView->SetWindowText(ActiveTitle);
		m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
		m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
		m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

		m_pGradView->SetDlgItemInt(IDC_INC_RED, nRed);
		m_pGradView->SetDlgItemInt(IDC_INC_GREEN, nGrn);
		m_pGradView->SetDlgItemInt(IDC_INC_BLUE, nBlu);

		//m_pGradView->SetDlgItemInt(IDC_MIN, min);
		//m_pGradView->SetDlgItemInt(IDC_MAX, max);

		m_pGradView->ScrollBarInit();
				
		if (bForward)
			m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
		else
			m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");
	}	
	else
	{
		bGradient = FALSE;
		m_pGradView->DestroyWindow();
	}	
}

void CFlarium24View::OnUpdateImageColorparameters(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bGradient);	

	pCmdUI->Enable(bInitialized);

//	if (m_pGradView->GetSafeHwnd() != 0)
//	{
//		m_pGradView->m_Forward.SetState(bForward);
//		m_pGradView->m_Reverse.SetState(!bForward);
//		//m_pGradView->m_Invert.SetState(TRUE);
//	}
}

long CFlarium24View::OnApply_GradView(UINT wParam, LONG lParam)
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return 0L;
	
	CFlarium24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (wParam == ID_DLGCLOSE)
	{
		bGradient = FALSE;
		m_pGradView->DestroyWindow();
	}	
	else
	{		
		m_pGradView->UpdateData(TRUE);

		nRedStart = m_pGradView->GetDlgItemInt(IDC_START_RED);
		nGrnStart = m_pGradView->GetDlgItemInt(IDC_START_GREEN);
		nBluStart = m_pGradView->GetDlgItemInt(IDC_START_BLUE);

		nRed  = m_pGradView->GetDlgItemInt(IDC_INC_RED);
		nGrn  = m_pGradView->GetDlgItemInt(IDC_INC_GREEN);
		nBlu  = m_pGradView->GetDlgItemInt(IDC_INC_BLUE);

		//min	  = m_pGradView->GetDlgItemInt(IDC_MIN);
		//max 	= m_pGradView->GetDlgItemInt(IDC_MAX);
		
		if (bForward)
			m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
		else
			m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

//		if (nColorMethod > 22)
//		{
//			bDraw = TRUE;  // ??
//			bLaunch = FALSE;
//		}
//		else
		{
			//if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
				//													nGrnStart, nBluStart, mIter_Data))

		if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
																nGrnStart, nBluStart,
																rIter_Data, gIter_Data, bIter_Data,
																nColorOrder))

			AfxMessageBox("Color shift error");
		}

		Invalidate(FALSE);
	}
	return 0L;
}

void CFlarium24View::OnDrawOrientation() 
{
	COrient co;
	co.m_Real = cOrient.real();
	co.m_Imag = cOrient.imag();
	if (co.DoModal() == IDOK)
	{
		cOrient.set_real(co.m_Real);
		cOrient.set_imag(co.m_Imag);
		bZeroInit = TRUE;
		GoDoFractal();
	}	
}

void CFlarium24View::OnDrawZeroinit() 
{
	bZeroInit ^= 1;	
	GoDoFractal();
}

void CFlarium24View::OnUpdateDrawZeroinit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bZeroInit);	
}

/////////////////////////////////////////////////////////////////////////
// Biomorphs
/////////////////////////////////////////////////////////////////////////

void CFlarium24View::OnFractalBiomorphnone() 
{
	dBiomorph = 0;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFractalBiomorphnone(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);

}

void CFlarium24View::OnFractal1biomorphxory() 
{
	dBiomorph = 1;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFractal1biomorphxory(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);
}

void CFlarium24View::OnFractalBiomorph() 
{
	dBiomorph = 2;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFractalBiomorph(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);
}

void CFlarium24View::OnFractalBiomorphtestxory() 
{
	dBiomorph = 3;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateFractalBiomorphtestxory(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);
}

void CFlarium24View::OnDrawBiomorph4() 
{
	dBiomorph = 4;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateDrawBiomorph4(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);
}

void CFlarium24View::OnDrawBiomorph5() 
{
	dBiomorph = 5;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateDrawBiomorph5(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);
}

void CFlarium24View::OnDrawBiomorph6() 
{
	dBiomorph = 6;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateDrawBiomorph6(CCmdUI* pCmdUI) 
{
	if (dBiomorph == 6)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

//	if (bMSet || bFSet)
//		pCmdUI->Enable(TRUE);
//	else
//		pCmdUI->Enable(FALSE);
}

void CFlarium24View::OnDrawMsetmethod() 
{
	bFSet = FALSE;
	bMSet ^= TRUE;  // Invert the M-Set flag	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateDrawMsetmethod(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bMSet);	
}

void CFlarium24View::OnDrawFset() 
{
	bMSet = FALSE;
	bFSet ^= TRUE;  // Invert the F-Set flag	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CFlarium24View::OnUpdateDrawFset(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bFSet);	
}

void CFlarium24View::OnViewStretchtofit() 
{
	bStretchToFit ^= 1;	
	Invalidate();
}

void CFlarium24View::OnUpdateViewStretchtofit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bStretchToFit);	
}


void CFlarium24View::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component

	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_FLARIUM24_VIEW));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

BOOL CFlarium24View::PreTranslateMessage(MSG* pMsg)
{
	// CG: This block was added by the Pop-up Menu component
	{
		// Shift+F10: show pop-up menu.
		if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
			(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||	// it's Shift+F10 OR
			(pMsg->message == WM_CONTEXTMENU))									// Natural keyboard key
		{
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			CPoint point = rect.TopLeft();
			point.Offset(5, 5);
			OnContextMenu(NULL, point);

			return TRUE;
		}
	}

	return CScrollView::PreTranslateMessage(pMsg);
}

void CFlarium24View::OnImageClear() 
{
	Clearselection(TRUE);	
}

void CFlarium24View::OnImageAspectratio() 
{
	bGenesisMode ^= TRUE;
}

void CFlarium24View::OnUpdateImageAspectratio(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bGenesisMode);	
}


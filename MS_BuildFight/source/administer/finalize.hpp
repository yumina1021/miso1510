//=============================================================================
// FileName: safeDelete.hpp
// Author: SHUN SAKAI
// Content: セーフデリート
//=============================================================================

//*****************************************************************************
// IncludeGurd
//*****************************************************************************
#ifndef _SAFE_DELETE_HPP_
#define _SAFE_DELETE_HPP_

//*****************************************************************************
// Include
//*****************************************************************************

//*****************************************************************************
// Link
//*****************************************************************************

//*****************************************************************************
// Macro
//*****************************************************************************

//=============================================================================
// FunctionName: SafeDelete
// Param: テンプレート型のポインタ
// ReturnValue: void
// Content: 引数のインスタンスを削除する
//=============================================================================
template <typename T>
inline void SafeDelete(T*& paramPtr){

	// インスタンスの破棄
	delete paramPtr;

	// お片づけ
	paramPtr = nullptr;

}// Create
//=============================================================================
// FunctionName: SafeDeleteArray
// Param: テンプレート型のポインタ
// ReturnValue: void
// Content: 引数のインスタンスの配列をを削除する
//=============================================================================
template <typename T>
inline void SafeDeleteArray(T*& paramPtr){

	// インスタンスの破棄
	delete[] paramPtr;

	// お片づけ
	paramPtr = nullptr;

}// Create
//=============================================================================
// FunctionName: SafeRelease
// Param: テンプレート型のポインタ
// ReturnValue: void
// Content: 引数のインスタンスのRelease関数を呼び出す
//=============================================================================
template <class T>
inline void SafeRelease(T*& paramPtr){

	if (paramPtr != nullptr){

		paramPtr->Release();
		paramPtr = nullptr;
	
	}// if
}
//*****************************************************************************
// IncludeGurd
//*****************************************************************************
#endif// _SAFE_DELETE_HPP_

// EOF
#ifndef _TESTINGFORM_H
#define _TESTINGFORM_H
#include <Windows.h>

BOOL CALLBACK TestingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TestingForm_OnSubmitButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // !_TESTINGFORM_H
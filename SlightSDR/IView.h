#pragma once


class IView {
public:
	//virtual void InvalidateAll() = 0;

	virtual void SetPlayStatus() = 0;
	virtual void SetStopStatus() = 0;
};
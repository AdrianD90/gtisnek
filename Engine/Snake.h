#pragma once
#include "Board.h"
#include <assert.h>


class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& deltaLoc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const { return loc; }
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& deltaLoc);
	Location GetNextHeadLocation(const Location& deltaLoc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};
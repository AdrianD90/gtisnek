#include "Snake.h"

Snake::Snake(const Location & loc) {
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{10, 100, 32},
		{10, 130, 48},
		{10, 160, 48},
		{10, 130, 48}
	};

	for (int i = 0; i < nSegmentsMax; ++i) {
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	}
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & deltaLoc) {
	for (int i = nSegments - 1; i > 0; --i) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(deltaLoc);
}

Location Snake::GetNextHeadLocation(const Location & deltaLoc) const {
	Location l(segments[0].GetLocation());
	l.Add(deltaLoc);
	return l;
}

void Snake::Grow() {
	if (nSegments < nSegmentsMax) {
		++nSegments;
	}
}

void Snake::Draw(Board & brd) const {
	for (int i = 0; i < nSegments; ++i) {
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location& target) const {
	for (int i = 0; i < nSegments - 1; ++i) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const {
	for (int i = 0; i < nSegments; ++i) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location& inLoc) {
	loc = inLoc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color cc) {
	c = cc;
}

void Snake::Segment::Follow(const Segment& next) {
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& deltaLoc) {
	assert(abs(deltaLoc.x) + abs(deltaLoc.y) == 1);
	loc.Add(deltaLoc);
}

void Snake::Segment::Draw(Board& brd) const {
	brd.DrawCell(loc, c);
}

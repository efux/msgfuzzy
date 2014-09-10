#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

class GridPosition {
	private:
		int x,y;
	public:
		GridPosition()
		{
			x=-1;
			y=-1;
		}

		GridPosition (int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		bool operator<( const GridPosition& other) const
		{
			if(x == other.x) {
				return y < other.y;
			}

			return x < other.x;
		}
};

#endif

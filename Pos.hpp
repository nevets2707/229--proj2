
#ifndef __POS_H_
#define __POS_H_
class Pos
{
	private:
		int x;
		int y;
		int pathSize;
		Pos** path;
	public:
		Pos(int a, int b);

		virtual ~Pos();

		int getX();
		int getY();
		int getPathSize();
		Pos** getPath();
		
		void setPathSize(int oldSize);
		void makePath(int oldSize, Pos** oldPath);

		bool operator==(Pos* other);
		bool equals(Pos* other);
};
#endif

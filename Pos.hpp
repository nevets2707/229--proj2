
#ifndef __POS_H_
#define __POS_H_
class Pos
{
	private:
		int x;
		int y;

	public:
		Pos(int a, int b);

		virtual ~Pos();

		int getX();
		int getY();
		
		bool equal(Pos* other);
};
#endif

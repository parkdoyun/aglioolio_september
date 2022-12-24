#include <iostream>

using namespace std;

// ¹éÁØ 5373 - Å¥ºù
// simulation
// ÇÃ·¡Æ¼³Ñ 5

// ¸éµµ ½Ã°è / ¹Ý½Ã°è ¹æÇâÀ¸·Î µ¹·Á¾ß ÇÔ

int n;
char colors[6] = { 'w', 'y', 'r', 'o', 'g', 'b' }; // ÃÊ±âÈ­¿ë ¹è¿­
char cube[6][3][3] = 
{
	{{'w', 'w', 'w'}, {'w', 'w', 'w'}, {'w', 'w', 'w'}}, // À­¸é, Èò»ö
	{{'y', 'y', 'y'}, {'y', 'y', 'y'}, {'y', 'y', 'y'}}, // ¾Æ·§¸é, ³ë¶õ»ö
	{{'r', 'r', 'r'}, {'r', 'r', 'r'}, {'r', 'r', 'r'}}, // ¾Õ¸é, »¡°£»ö
	{{'o', 'o', 'o'}, {'o', 'o', 'o'}, {'o', 'o', 'o'}}, // µÞ¸é, ¿À·»Áö»ö
	{{'g', 'g', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}}, // ¿ÞÂÊ¸é, ÃÊ·Ï»ö
	{{'b', 'b', 'b'}, {'b', 'b', 'b'}, {'b', 'b', 'b'}} // ¿À¸¥ÂÊ¸é, ÆÄ¶õ»ö
};
char tmp_arr[3];

void faceRotate(int face, char dir)
{
	for (int i = 0; i < 3; i++) tmp_arr[i] = cube[face][0][i];
	if (dir == '+') // ½Ã°è ¹æÇâ
	{
		for (int i = 0; i < 3; i++) cube[face][0][2 - i] = cube[face][i][0];
		for (int i = 0; i < 3; i++) cube[face][i][0] = cube[face][2][i];
		for (int i = 0; i < 3; i++) cube[face][2][i] = cube[face][2 - i][2];
		for (int i = 1; i < 3; i++) cube[face][i][2] = tmp_arr[i];
	}
	else // ¹Ý½Ã°è
	{
		for (int i = 0; i < 3; i++) cube[face][0][i] = cube[face][i][2];
		for (int i = 0; i < 3; i++) cube[face][i][2] = cube[face][2][2 - i];
		for (int i = 0; i < 3; i++) cube[face][2][2 - i] = cube[face][2 - i][0];
		for (int i = 1; i < 3; i++) cube[face][i][0] = tmp_arr[2 - i];
	}
}

void rotate(char face, char dir)
{
	if (face == 'U')
	{
		faceRotate(0, dir);
		if (dir == '+') // ½Ã°è ¹æÇâ (¿Þ -> µÞ -> ¿À -> ¾Õ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[2][0][i]; // ¾Õ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[2][0][i] = cube[5][0][i]; // ¿À -> ¾Õ
			for (int i = 0; i < 3; i++) cube[5][0][i] = cube[3][0][i]; // µÞ -> ¿À
			for (int i = 0; i < 3; i++) cube[3][0][i] = cube[4][0][i]; // ¿Þ -> µÞ
			for (int i = 0; i < 3; i++) cube[4][0][i] = tmp_arr[i]; // ¾Õ -> ¿Þ
		}
		else // ¹Ý½Ã°è (¾Õ -> ¿À -> µÞ -> ¿Þ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[4][0][i]; // ¿Þ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[4][0][i] = cube[3][0][i]; // µÞ -> ¿Þ
			for (int i = 0; i < 3; i++) cube[3][0][i] = cube[5][0][i]; // ¿À -> µÞ
			for (int i = 0; i < 3; i++) cube[5][0][i] = cube[2][0][i]; // ¾Õ -> ¿À
			for (int i = 0; i < 3; i++) cube[2][0][i] = tmp_arr[i]; // ¿Þ -> ¾Õ
		}
	}
	else if (face == 'D')
	{
		faceRotate(1, dir);
		if (dir == '-') // ¹Ý½Ã°è ¹æÇâ (¿Þ -> µÞ -> ¿À -> ¾Õ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[2][2][i]; // ¾Õ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[2][2][i] = cube[5][2][i]; // ¿À -> ¾Õ
			for (int i = 0; i < 3; i++) cube[5][2][i] = cube[3][2][i]; // µÞ -> ¿À
			for (int i = 0; i < 3; i++) cube[3][2][i] = cube[4][2][i]; // ¿Þ -> µÞ
			for (int i = 0; i < 3; i++) cube[4][2][i] = tmp_arr[i]; // ¾Õ -> ¿Þ
		}
		else // ½Ã°è (¾Õ -> ¿À -> µÞ -> ¿Þ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[4][2][i];
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i]; // µÞ -> ¿Þ
			for (int i = 0; i < 3; i++) cube[3][2][i] = cube[5][2][i]; // ¿À -> µÞ
			for (int i = 0; i < 3; i++) cube[5][2][i] = cube[2][2][i]; // ¾Õ -> ¿À
			for (int i = 0; i < 3; i++) cube[2][2][i] = tmp_arr[i]; // ¿Þ -> ¾Õ
		}
	}
	else if (face == 'F')
	{
		faceRotate(2, dir);
		if (dir == '+') // ½Ã°è (À­ -> ¿À -> ¾Æ -> ¿Þ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[4][i][2]; // ¿Þ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[4][i][2] = cube[1][2][2 - i]; // ¾Æ -> ¿Þ
			for (int i = 0; i < 3; i++) cube[1][2][i] = cube[5][i][0]; // ¿À -> ¾Æ
			for (int i = 0; i < 3; i++) cube[5][i][0] = cube[0][2][i]; // À­ -> ¿À
			for (int i = 0; i < 3; i++) cube[0][2][2 - i] = tmp_arr[i]; // ¿Þ -> À­
		}
		else // ¹Ý½Ã°è (¿Þ -> ¾Æ -> ¿À -> À­)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[0][2][i]; // À­
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[0][2][i] = cube[5][i][0]; // ¿À -> À­
			for (int i = 0; i < 3; i++) cube[5][i][0] = cube[1][2][i]; // ¾Æ -> ¿À
			for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2 - i][2]; // ¿Þ -> ¾Æ
			for (int i = 0; i < 3; i++) cube[4][2 - i][2] = tmp_arr[i]; // À­ -> ¿Þ
		}
	}
	else if (face == 'B')
	{
		faceRotate(3, dir);
		if (dir == '-') // ¹Ý½Ã°è (À­ -> ¿À -> ¾Æ -> ¿Þ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[4][i][0]; // ¿Þ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[4][i][0] = cube[1][0][2 - i]; // ¾Æ -> ¿Þ
			for (int i = 0; i < 3; i++) cube[1][0][i] = cube[5][i][2]; // ¿À -> ¾Æ
			for (int i = 0; i < 3; i++) cube[5][i][2] = cube[0][0][i]; // À­ -> ¿À
			for (int i = 0; i < 3; i++) cube[0][0][2 - i] = tmp_arr[i]; // ¿Þ -> À­
		}
		else // ½Ã°è (¿Þ -> ¾Æ -> ¿À -> À­)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[0][0][i]; // À­
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[0][0][i] = cube[5][i][2]; // ¿À -> À­
			for (int i = 0; i < 3; i++) cube[5][i][2] = cube[1][0][i]; // ¾Æ -> ¿À
			for (int i = 0; i < 3; i++) cube[1][0][i] = cube[4][2 - i][0]; // ¿Þ -> ¾Æ
			for (int i = 0; i < 3; i++) cube[4][2 - i][0] = tmp_arr[i]; // À­ -> ¿Þ
		}
	}
	else if (face == 'L') // ¿ÞÂÊ
	{
		faceRotate(4, dir);
		if (dir == '+') // ½Ã°è (¾Õ -> ¾Æ -> µÞ -> À­)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[0][i][0]; // À­
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[0][i][0] = cube[3][2 - i][2]; // µÞ -> À­
			for (int i = 0; i < 3; i++) cube[3][i][2] = cube[1][i][2]; // ¾Æ -> µÞ
			for (int i = 0; i < 3; i++) cube[1][i][2] = cube[2][2 - i][0]; // ¾Õ -> ¾Æ
			for (int i = 0; i < 3; i++) cube[2][i][0] = tmp_arr[i]; // À­ -> ¾Õ
		}
		else // ¹Ý½Ã°è (À­ -> µÞ -> ¾Æ -> ¾Õ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[2][i][0]; // ¾Õ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[2][i][0] = cube[1][2 - i][2]; // ¾Æ -> ¾Õ
			for (int i = 0; i < 3; i++) cube[1][i][2] = cube[3][i][2]; // µÞ -> ¾Æ
			for (int i = 0; i < 3; i++) cube[3][i][2] = cube[0][2 - i][0]; // À­ -> µÞ
			for (int i = 0; i < 3; i++) cube[0][i][0] = tmp_arr[i]; // ¾Õ -> À­
		}
	}
	else // R
	{
		faceRotate(5, dir);
		if (dir == '-') // ¹Ý½Ã°è (¾Õ -> ¾Æ -> µÞ -> À­)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[0][i][2]; // À­
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[0][i][2] = cube[3][2 - i][0]; // µÞ -> À­
			for (int i = 0; i < 3; i++) cube[3][i][0] = cube[1][i][0]; // ¾Æ -> µÞ
			for (int i = 0; i < 3; i++) cube[1][i][0] = cube[2][2 - i][2]; // ¾Õ -> ¾Æ
			for (int i = 0; i < 3; i++) cube[2][i][2] = tmp_arr[i]; // À­ -> ¾Õ
		}
		else // ½Ã°è (À­ -> µÞ -> ¾Æ -> ¾Õ)
		{
			for (int i = 0; i < 3; i++) tmp_arr[i] = cube[2][i][2]; // ¾Õ
			// ¿Å±â±â
			for (int i = 0; i < 3; i++) cube[2][i][2] = cube[1][2 - i][0]; // ¾Æ -> ¾Õ
			for (int i = 0; i < 3; i++) cube[1][i][0] = cube[3][i][0]; // µÞ -> ¾Æ
			for (int i = 0; i < 3; i++) cube[3][i][0] = cube[0][2 - i][2]; // À­ -> µÞ
			for (int i = 0; i < 3; i++) cube[0][i][2] = tmp_arr[i]; // ¾Õ -> À­
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	char face, dir; // ¸é, µ¹¸° ¹æÇâ
	for (int tc = 1; tc <= T; tc++)
	{
		// Å¥ºê ÃÊ±âÈ­
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int r = 0; r < 3; r++) cube[i][j][r] = colors[i];
			}
		}

		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> face >> dir;

			rotate(face, dir);

		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << cube[0][i][j];
			}
			cout << '\n';
		}
	}

	return 0;
}
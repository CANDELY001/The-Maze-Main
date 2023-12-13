#include "../headers/header.h"
player_t player;
/**
 * display_player - Function to display the player on the screen.
 * @instance: The given SDL2 instance.
 *
 * This function renders the player's rectangle and line of sight.
 */
void display_player(SDL_Instance instance)
{
    /** Variables for the initial & final coordinates and SDL_Rect. */
    SDL_Rect rect;
    float x0, y0, x1, y1;

    /** Convert the player position into map scale. */
    rect.x = player.x * MAP_SCALE;
    rect.y = player.y * MAP_SCALE;
    rect.w = player.w * MAP_SCALE;
    rect.h = player.w * MAP_SCALE;

    /** Draw the rectangle of the player. */
    SDL_SetRenderDrawColor(instance.ren, 255, 255, 0, 0);
    SDL_RenderFillRect(instance.ren, &rect);

    /** Draw the line of sight of the player. */
    x0 = player.x * MAP_SCALE;
    y0 = player.y * MAP_SCALE;
    x1 = (player.x + player.dx * 20) * MAP_SCALE;
    y1 = (player.y + player.dy * 20) * MAP_SCALE;
    SDL_RenderDrawLine(instance.ren, x0, y0, x1, y1);
}

/**
 * drawRect - draw a rectangle
 * @x: x coordinate
 * @y: y coordinate
 * @width: rectangle width
 * @height: rectangle height
 * @color: pixel color
*/

void drawRect(int x, int y, int width, int height, color_t color)
{
	int i, j;

	for (i = x; i <= (x + width); i++)
		for (j = y; j <= (y + height); j++)
			drawPixel(i, j, color);
}

/**
 * drawLine - draw a line
 * @x0: x coordinate init
 * @y0: y coordinate init
 * @x1: x coordinate init
 * @y1: y coordinate end
 * @color: pixel color
*/

void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
	float xIncrement, yIncrement, currentX, currentY;
	int i, longestSideLength, deltaX,  deltaY;

	deltaX = (x1 - x0);
	deltaY = (y1 - y0);

	longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

	xIncrement = deltaX / (float)longestSideLength;
	yIncrement = deltaY / (float)longestSideLength;

	currentX = x0;
	currentY = y0;

	for (i = 0; i < longestSideLength; i++)
	{
		drawPixel(round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
	}
}

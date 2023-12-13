#include "../headers/header.h"

enemy_t enemies[num_enemy] = {
	{79.4, 84.4, 0, "images/enm.png"},
	{250.5, 100, 5, "images/enm222.png"},
	{390.5, 205, 5, "images/enm33.png"},
	{430, 384, 5, "images/enm.png"},
	{80.3, 445.7, 5, "images/enm111.png"}
};
/**
 * add_enemy - function to draw an enemy
 * @ins: the given instance
 *
 * Return: nothing
 **/
void add_enemy(SDL_Instance ins)
{
    int i;

    for (i = 0; i < num_enemy; i++)
    {
        /** get the texture from wallTextures **/
        upng_t *enemyTexture = wallTextures[num_enemy].upngTexture;
        if (enemyTexture != NULL)
        {
            SDL_Texture *texture = NULL;
            SDL_Rect en;
            int w, h;

            w = wallTextures[num_enemy].width;
            h = wallTextures[num_enemy].height;

            float dx = enemies[i].x - player.x, dy = enemies[i].y - player.y;
            float ds = sqrt(dx * dx + dy * dy);
            float e_a = atan2(dy, dx) - player.a, e_d = cos(e_a) * ds;
            float DPP = find_viewdistance(), e_swidth = map_s * DPP / e_d;
            float sx = tan(e_a) * DPP;

            en.x = (SCREEN_WIDTH / 2) + sx - (e_swidth / 2);
            float ex = e_d / 4;
            en.y = (SCREEN_HEIGHT - e_swidth) / 2.0f;
            en.w = e_swidth;
            en.h = e_swidth;

            /** draw the enemy with the above specification **/
            SDL_UpdateTexture(texture, NULL, wallTextures[num_enemy].texture_buffer, w * sizeof(color_t));
            SDL_RenderCopy(ins.ren, texture, NULL, &en);
        }
        else
            printf("Unable to get enemy texture\n");
    }
}
/**
 * add_weapon - function to draw a weapon
 * @ins: the given instance
 *
 * Return: nothing
 **/
void add_weapon(SDL_Instance ins)
{
    /** variables for the sdl, width & height **/
    SDL_Texture *texture = NULL;
    SDL_Rect gun;
    int w, h;

    /** get the texture from wallTextures **/
    SDL_Surface *surf = IMG_Load("images/gn111.png");

    /** if the image found **/
    if (surf)
    {
        /** remove the background white color **/
        SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 255, 255));
        /** create a texture **/
        texture = SDL_CreateTextureFromSurface(ins.ren, surf);
        /** query the texture to find width & height of the image **/
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        gun.w = w * gun_scale, gun.h = h * gun_scale;
        gun.x = (SCREEN_WIDTH - gun.w) / 2;
        gun.y = (SCREEN_HEIGHT - gun.h) + 20;

        /** draw the weapon with the above specification **/
        if (texture)
            SDL_RenderCopy(ins.ren, texture, NULL, &gun);
        else
            printf("unable to create texture\n");
        /** free & destroy the surface **/
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(texture);
    }
    else
        printf("unable to create a surface\n");
}

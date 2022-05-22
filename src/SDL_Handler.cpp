#include "SDL_Handler.hpp"

#include "Geometry.hpp"

SDL_Handler::SDL_Handler(const Vector2u16 SCREEN_SIZE)
: SCREEN_SIZE{SCREEN_SIZE}
{
    sdl_setup();
}

void SDL_Handler::sdl_setup()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Init error: %s\n", SDL_GetError());
    }
    else
    {
        this->window = SDL_CreateWindow("Boar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->SCREEN_SIZE.x, this->SCREEN_SIZE.y, SDL_WINDOW_SHOWN);
        if (this->window == NULL)
        {
            printf("Window creating error: %s\n", SDL_GetError());
        }
        else 
        {
            renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
			if( renderer == NULL )
            {
                printf( "Renderer  Error: %s\n", SDL_GetError() );
            }
			else{
				SDL_SetRenderDrawColor(renderer, 0,0,0,0);
			}
        }

    }
}



SDL_Handler::~SDL_Handler()
{
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SDL_Handler::loop()
{
    SDL_Event event;

	while (true)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT) {
				return;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				//Moves the player
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					raytracer.camera_pos.y += 0.1;
					continue;
				case SDLK_s:
					raytracer.camera_pos.y -= 0.1;
					continue;
				case SDLK_d:
					raytracer.camera_pos.x += 0.1;
					continue;
				case SDLK_a:
					raytracer.camera_pos.x -= 0.1;
					continue;
				}
				

			}
        }

		render_screen();
    }
}

void SDL_Handler::render_screen()
{
    SDL_RenderClear(renderer);

    for(int16_t x = -SCREEN_SIZE.x/2;x<SCREEN_SIZE.x/2;x++)
    {
        for(int16_t y = -SCREEN_SIZE.y/2; y<SCREEN_SIZE.y/2;y++)
        {
            const Vector2i16 screen_pos{x,y};
            const Vector3d dir = raytracer.screen_to_viewport(screen_pos);
            const SDL_Color color = raytracer.raytrace(dir);
            SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
            SDL_RenderDrawPoint(renderer,x+SCREEN_SIZE.x/2,-y + SCREEN_SIZE.y/2);
        }
    }
    
    SDL_RenderPresent(renderer);
}
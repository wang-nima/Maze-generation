/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
 and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_set>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Nothing to load
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

struct Cell {
    int x;      // position
    int y;
    int size;
    
    bool up;
    bool down;
    bool left;
    bool right;
    
    Cell (int size) {
        this->size = size;
        up = down = left = right = false;
    }
};

void drawRect(const Cell &r) {
    
    int offset = 20;
    
    SDL_Rect rect = {r.y + offset, r.x + offset, r.size, r.size};
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderDrawRect( gRenderer, &rect);
}

void displayBoard(const vector<vector<Cell>> &board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            drawRect(board[i][j]);
        }
    }
}

int getRand4() {
    return rand() % 4;
}

const int m = 30;              // the number of rows
const int n = 40;              // the number of columns
vector<vector<bool>> visited(m, vector<bool>(n, false));

int getRandomLegalDirection(int i, int j, const vector<vector<Cell>> &board) {
    int count = 0;
    unordered_set<int>  tried;
    while (tried.size() < 4) {
        int rand = getRand4();
        tried.insert(rand);
        if (rand == 0) {
            if (i - 1 >= 0 && !visited[i-1][j]) {
                return 0;
            }
        } else if (rand == 1) {
            if (i + 1 < m && !visited[i+1][j]) {
                return 1;
            }
        } else if (rand == 2) {
            if (j - 1 >= 0 && !visited[i][j-1]) {
                return 2;
            }
        } else {    // rand == 3
            if (j + 1 < n && !visited[i][j+1]) {
                return 3;
            }
        }
        count++;
    }
    // no feasible direction
    return -1;
}

vector<int> getRandomPermutation4() {
    vector<int> ret;
    unordered_set<int> s;
    while (s.size() < 4) {
        int temp = getRand4();
        s.insert(temp);
        if (s.find(temp) == s.end()) {
            ret.push_back(temp);
        }
    }
    return ret;
}


void getPath(vector<vector<Cell>> &board) {
    stack<Cell> stk;
    stk.push(board[0][0]);
    while (!stk.empty()) {
        Cell temp = stk.top();
        stk.pop();
        int x = temp.x;
        int y = temp.y;
        visited[x][y] = true;
        // push all possible move to stack
        vector<int> sequence = getRandomPermutation4();
        
        for (int i = 0; i < 4; i++) {
            if (sequence[i] == 0) {
                
            } else if
        }
     }
}


int main( int argc, char* args[] )
{
    const int size = 20;
    // do computation here
    vector<vector<Cell>> board(m, vector<Cell>(n, Cell(size)));
    srand((int)time(0));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j].x = i * size;
            board[i][j].y = j * size;
        }
    }
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                displayBoard(board);
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}
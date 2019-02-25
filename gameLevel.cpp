#include "GameLevel.h"

#include <fstream>
#include <sstream>


void GameLevel::Load(const char *file, float levelWidth, float levelHeight){
    // Clear old data
    this->bricks.clear();
    // Load from file
    int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<int> > tileData;
    if (fstream){
	// Read each line from level file
        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<int> row;
	    // Read each word seperated by spaces
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::draw(){
    for (Brick &block : this->bricks)
        if (!block.isDestroyed())
            block.draw();
}

bool GameLevel::isCompleted(){
    for (Brick &block : this->bricks)
        if (!block.isSolid() && !block.isDestroyed())
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<int> > tileData, float levelWidth, float levelHeight){
    // Calculate dimensions
    float height = tileData.size();
    float width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<int>(width);
    float unit_height = levelHeight / height; 
    // Initialize level tiles based on tileData		
    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            // Check block type from level data (2D level array)
	    // Solid
            if (tileData[y][x] == 1) {
		float blockX = unit_width * x;
		float blockY = unit_height * y;
		float blockW = unit_width;
		float blockH = unit_height;
                Brick bric("images/block_solid.png", blockX, blockY, blockW, blockH, 0.8f, 0.8f, 0.7f);
                bric.setSolid(true);
                this->bricks.push_back(bric);
            }
	    // Non-solid; now determine its color based on level data
            else if (tileData[y][x] > 1){
		float r, g, b = 1.0f; // original: white
                if (tileData[y][x] == 2){
		    r = 0.2f;
		    g = 0.6f;
		    b = 1.0f;
		}
                else if (tileData[y][x] == 3){
		    r = 0.0f;
		    g = 0.7f;
		    b = 0.0f;
		}
                else if (tileData[y][x] == 4){
		    r = 0.8f;
		    g = 0.8f;
		    b = 0.4f;
		}
                else if (tileData[y][x] == 5){
		    r = 1.0f;
		    g = 0.5f;
		    b = 0.0f;
		}
                float blockX = unit_width * x;
		float blockY = unit_height * y;
		float blockW = unit_width;
		float blockH = unit_height;
                this->bricks.push_back(Brick("images/block.png", blockX, blockY, blockW, blockH, r, g, b));
            }
        }
    }
}

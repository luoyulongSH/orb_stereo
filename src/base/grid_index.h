//
// Created by luoyulong on 18/5/6.
//

#ifndef ORB_STEREO_MAPPING_GRID_INDEX_H
#define ORB_STEREO_MAPPING_GRID_INDEX_H
#include <functional>
#include <vector>
#include "../data_type.h"
namespace orb
{
    class GridIndex
    {
    public:
        GridIndex(int image_width, int image_height, int cell_width, int cell_height): cell_width_(cell_width), cell_height_(cell_height)
        {
            int num_cell_x = ( int )( image_width / cell_width  + 0.5 );
            int num_cell_y = ( int )( image_height / cell_height + 0.5 );

            grid_index_vecs.resize(num_cell_x);
            for ( int x = 0; x < num_cell_x; ++x )
            {
                grid_index_vecs[x].resize(num_cell_y);
                for (int y = 0; y < num_cell_y; ++y)
                {
                    grid_index_vecs[y].resize(20);
                }
            }
        }

        void InitOneByOne( int u, int v, size_t index )
        {
            static CellIndex grid_index;
            CalcIndex(u, v, &grid_index);

            grid_index_vecs[grid_index.x][grid_index.y].push_back(index);

        }

        void CalcIndex( const Point& point,  CellIndex* grid_index)
        {
            CalcIndex( point.x, point.y, grid_index );
        }

        void CalcIndex( int cell_x, int cell_y, CellIndex* cell_index)
        {
            cell_index->x = cell_x / cell_width_;
            cell_index->y = cell_y / cell_height_;
        }

        void SearchByFilter( const Rect& rect, const std::function<void (size_t)>& filter )
        {
            CellIndex grid_index1, grid_index2;
            CalcIndex(rect.x, rect.y, &grid_index1);
            CalcIndex(rect.x + rect.width, rect.y + rect.height, &grid_index2);

            for (int i = grid_index1.x; i < grid_index2.x; ++i)
            {
                for (int j = grid_index1.y; j < grid_index2.y; ++j)
                {
                    const std::vector<size_t>& indexs = grid_index_vecs[i][j];
                    for ( size_t index: indexs)
                    {
                        filter(index);
                    }
                }
            }
        }

        void Search( const Rect& rect, std::vector<size_t>* index_vec )
        {
            CellIndex grid_index1, grid_index2;
            CalcIndex(rect.x, rect.y, &grid_index1);
            CalcIndex(rect.x + rect.width, rect.y + rect.height, &grid_index2);

            for (int i = grid_index1.x; i < grid_index2.x; ++i)
            {
                for (int j = grid_index1.y; j < grid_index2.y; ++j)
                {
                    const std::vector<size_t>& indexs = grid_index_vecs[i][j];
                    index_vec->insert(index_vec->end(), indexs.begin(), indexs.end());
                }
            }
        }


    private:
        int cell_width_;
        int cell_height_;

        std::vector<std::vector<std::vector<size_t >>> grid_index_vecs;
    };
}

#endif //ORB_STEREO_MAPPING_GRID_INDEX_H

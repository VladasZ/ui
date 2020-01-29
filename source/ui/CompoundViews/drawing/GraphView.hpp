//
//  GraphView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "DrawingView.hpp"

namespace ui {

class GraphView : public View {

    gm::PointsPath* _path = nullptr;

    std::vector<float> _points;

    DrawingView* _drawing_view = nullptr;

    size_t _points_size = 1000;
    float _multiplier   = 1.0f;

public:

    using View::View;

    bool flip_data = false;

    gm::Color graph_color;

    ~GraphView() override;

    size_t points_size() const;
    void set_points_size(size_t);

    float multiplier() const;
    void set_multiplier(float);

    void add_point(float);
    void reset();

protected:

    float _delta() const;
    void _setup() override;
    void _layout() override;
    void _recalculate_graph();

};

}

//
//  ChartView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <array>

#include "GraphView.hpp"

namespace ui {

class ChartView : public View {

    std::vector<GraphView*> _graphs;

public:

    using View::View;

    size_t size() const;
    void set_size(size_t);

    void add_values(const std::initializer_list<float>&);

    void set_colors(const std::initializer_list<gm::Color>&);

    void set_points_size(size_t);
    void set_multiplier(float);

    void reset();

private:

    void _setup() override;
    void _layout() override;

};

}

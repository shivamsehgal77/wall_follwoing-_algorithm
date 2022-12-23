#include "cps.h"


int rwa2group2::Robot::get_position_x() {
    return m_position.first;
}

int rwa2group2::Robot::get_position_y() {
    return m_position.second;
}

char rwa2group2::Robot::get_direction() {
    return m_direction;
}

void rwa2group2::Robot::turn_left() {
    Simulator::turnLeft();
    if (m_direction == 'n') {
        m_direction = 'w';
    } 
    else if (m_direction == 'w') {
        m_direction = 's';
    } 
    else if (m_direction == 's') {
        m_direction = 'e';
    } 
    else {
        m_direction = 'n';
    }
}
void rwa2group2::Robot::turn_right() {
    Simulator::turnRight();
    if (m_direction == 'n') {
        m_direction = 'e';
    } 
    else if (m_direction == 'e') {
        m_direction = 's';
    } 
    else if (m_direction == 's') {
        m_direction = 'w';
    } 
    else {
        m_direction = 'n';
    }
}
void rwa2group2::Robot::move_forward() {
    Simulator::moveForward();
    // the after moving forward the m_psition is changed based on the direction
    // if north or south y is changed
    // if east or west x is changed
    if (m_direction == 'n') {
        m_position.second++;
    } 
    else if (m_direction == 'e') {
        m_position.first++;
    } 
    else if (m_direction == 's') {
        m_position.second--;
    } 
    else {
        m_position.first--;
    }
}

void rwa2group2::Cell::init_cell_walls() {
    m_walls = {false, false, false, false};
}


void rwa2group2::Cell::set_wall(std::pair<int, int> m_position) {
    
    for (int i = 0; i < 4; i++) {
        // if the wall is present in a give direction is color is set
        if (m_walls.at(i) == true) {
            Simulator::setWall(m_position.first, m_position.second, directions.at(i));
        }
    }
}

void rwa2group2::Cell::is_wall(char wall) {
    
    // switch case to set the m_wall for each direction
    switch (wall) {
        case ('n'):
            if (Simulator::wallFront() == true) {
                m_walls.at(0) = true;
            }
            if (Simulator::wallRight() == true) {
                m_walls.at(1) = true;
            }
            if (Simulator::wallLeft() == true) {
                m_walls.at(3) = true;
            }

            break;
        case ('e'):
            if (Simulator::wallFront() == true) {
                m_walls.at(1) = true;
            }
            if (Simulator::wallRight() == true) {
                m_walls.at(2) = true;
            }
            if (Simulator::wallLeft() == true) {
                m_walls.at(0) = true;
            }

            break;
        case ('s'):
            if (Simulator::wallFront() == true) {
                m_walls.at(2) = true;
            }
            if (Simulator::wallRight() == true) {
                m_walls.at(3) = true;
            }
            if (Simulator::wallLeft() == true) {
                m_walls.at(1) = true;
            }

            break;
        case ('w'):
            if (Simulator::wallFront() == true) {
                m_walls.at(3) = true;
            }
            if (Simulator::wallRight() == true) {
                m_walls.at(0) = true;
            }
            if (Simulator::wallLeft() == true) {
                m_walls.at(2) = true;
            }

            break;
    }
}


void rwa2group2::Algorithm::init_outer_walls() {
    // Two for loops are used to set the outer walls
    // Conditions applied on x and y to set just the outer walls
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y <= 15; y++) {
            if (x == 0) {
                Simulator::setWall(x, y, 'w');
            }
            if (x == 15) {
                Simulator::setWall(x, y, 'e');
            }
            if (y == 0) {
                Simulator::setWall(x, y, 's');
            }
            if (y == 15) {
                Simulator::setWall(x, y, 'n');
            }
        }
    }
}

void rwa2group2::Algorithm::follow_wall_left() {

    init_outer_walls();
    std::pair<int, int> goal = generate_goal();

    // Prints out initial position
    
    std::cerr << "INITIAL DIRECTION = 0"
              << "\n";
    std::cerr << "INITIAL POSITION x= 0"
              << "\n";
    std::cerr << "INITIAL POSITION y= 0"
              << "\n";
            
    // While the goal is not reached the loop runs
    while (!(robot->m_position.first == goal.first && robot->m_position.second == goal.second)) {
        
        // To store the path followed by robot to reach the goal
        path.push_back(robot->m_position);

        // Checks and sets walls using the cell class
        m_maze.at(robot->m_position.first).at(robot->m_position.second).is_wall(robot->m_direction);
        m_maze.at(robot->m_position.first).at(robot->m_position.second).set_wall(robot->m_position);

        // Prints current position of the robot
        std::cerr << "cURRENT DIRECTION OF THE ROBOT = " << robot->get_direction() << '\n';
        std::cerr << "cURRENT x POSITION OF THE ROBOT = " << robot->get_position_x() << '\n';
        std::cerr << "CURRENT y POSITION OF THE ROBOT = " << robot->get_position_y() << '\n';
        
        Simulator::setColor(robot->m_position.first, robot->m_position.second, 'C');

        // left wall algorithm
        if (!Simulator::wallLeft()) {
            robot->turn_left();
            robot->move_forward();

        } else if (!Simulator::wallFront()) {
            robot->move_forward();
        } else if (!Simulator::wallRight()) {
            robot->turn_right();
            robot->move_forward();
        } else {
            robot->turn_left();
            robot->turn_left();
            robot->move_forward();
        }
    }

    // Store the last position when loop ends
    path.push_back(robot->m_position);

    //Clear the color set by the followed path
    Simulator::clearAllColor();

    // Sets the last wall when the loop ends
    m_maze.at(robot->m_position.first).at(robot->m_position.second).is_wall(robot->m_direction);
    m_maze.at(robot->m_position.first).at(robot->m_position.second).set_wall(robot->m_position);

    // Prints the last position of the robot
    std::cerr << "CURRENT DIRECTION OF THE ROBOT = " << robot->get_direction() << '\n';
    std::cerr << "CURRENT x POSITION OF THE ROBOT = " << robot->get_position_x() << '\n';
    std::cerr << "CURRENT y POSITION OF THE ROBOT = " << robot->get_position_y() << '\n';

    // Generates the best path for the robot to follow
    generate_best_path(path);

    std::cerr << "We are going home"
              << "\n";
    
    // Makes the robot follow the best path
    go_home(path);
}


void rwa2group2::Algorithm::follow_wall_right() {
    
    init_outer_walls();
    std::pair<int, int> goal = generate_goal();

    // Prints out initial position
    std::cerr << "INITIAL DIRECTION = 0"
              << "\n";
    std::cerr << "INITIAL POSITION x= 0"
              << "\n";
    std::cerr << "INITIAL POSITION y= 0"
              << "\n";

    // While the goal is not reached the loop runs          
    while (!(robot->m_position.first == goal.first && robot->m_position.second == goal.second)) {
        
        path.push_back(robot->m_position);

        
        m_maze.at(robot->m_position.first).at(robot->m_position.second).is_wall(robot->m_direction);
        m_maze.at(robot->m_position.first).at(robot->m_position.second).set_wall(robot->m_position);

       
        std::cerr << "cURRENT DIRECTION OF THE ROBOT = " << robot->get_direction() << '\n';
        std::cerr << "cURRENT x POSITION OF THE ROBOT = " << robot->get_position_x() << '\n';
        std::cerr << "CURRENT y POSITION OF THE ROBOT = " << robot->get_position_y() << '\n';
        Simulator::setColor(robot->m_position.first, robot->m_position.second, 'C');

        if (!Simulator::wallRight()) {
            robot->turn_right();
            robot->move_forward();

        } else if (!Simulator::wallFront()) {
            robot->move_forward();
        } else if (!Simulator::wallLeft()) {
            robot->turn_left();
            robot->move_forward();
        } else {
            robot->turn_right();
            robot->turn_right();
            robot->move_forward();
        }
    }
    path.push_back(robot->m_position);
    Simulator::clearAllColor();
    m_maze.at(robot->m_position.first).at(robot->m_position.second).is_wall(robot->m_direction);
    m_maze.at(robot->m_position.first).at(robot->m_position.second).set_wall(robot->m_position);

    std::cerr << "cURRENT DIRECTION OF THE ROBOT = " << robot->get_direction() << '\n';
    std::cerr << "cURRENT x POSITION OF THE ROBOT = " << robot->get_position_x() << '\n';
    std::cerr << "CURRENT y POSITION OF THE ROBOT = " << robot->get_position_y() << '\n';

    generate_best_path(path);

    std::cerr << "We are going home"
              << "\n";
    go_home(path);
}

std::pair<int, int> rwa2group2::Algorithm::generate_goal() {
    //srand to generate differnt random numbers based on time
    srand(time(0));
    
    int x;
    int y;
    const std::string &text{"G"};
    std::array<int, 2> arr{0, 15};
    char tryagain{'y'};
    // using r random number b/w 0 and 1 is selected
    int r = rand() % 2;
    // using a a random number between 0 and 1 is selected
    int a = rand() % 2;

    // If else generates random x and y on the outr walls using the r and a
    if (r == 1) {
        x = arr[a];
        y = rand() % 16;
    } else {
        y = arr[a];
        x = rand() % 16;
    }

    Simulator::setText(x, y, "G");
    Simulator::setColor(x, y, 'R');


    std::pair<int, int> final_goal{x, y};

    return final_goal;
}

void rwa2group2::Algorithm::generate_best_path(std::vector<std::pair<int, int>> &path) {

    Simulator::setColor(0, 0, 'w');
    // for loop is used to compare the elements of path with itself
    // when same element is found it delets everything after the ith element till the jth element found same(including jth element)
    // when the condition is met j is set to i again so that no comparision is left
    for (auto i = 0; i < path.size(); ++i) {
        for (auto j = i + 1; j < path.size(); ++j) {
            if (path.at(i).first == path.at(j).first && path.at(i).second == path.at(j).second) {
                path.erase(path.begin() + i + 1, path.begin() + j + 1);
                j = i;
            }
        }
    }
}

void rwa2group2::Algorithm::go_home(std::vector<std::pair<int, int>> &path) {
    // runs the loop until home posiiton is used 
    while (!(robot->m_position.first == 0 && robot->m_position.second == 0)) {

        // Sets the color of the path followed by robot to cyan
        Simulator::setColor(robot->m_position.first, robot->m_position.second, 'C');
        //deletes the path the has been coverd
        path.pop_back();

        // Algorithm to move the robot given the nect position and direction
        if (robot->m_position.first - path.back().first == -1) {
            while (robot->m_direction != 'e') {
                if (robot->m_direction == 'n') {
                    robot->turn_right();
                } else {
                    robot->turn_left();
                }
            }
        } else if (robot->m_position.first - path.back().first == 1) {
            while (robot->m_direction != 'w') {
                if (robot->m_direction == 's') {
                    robot->turn_right();
                } else {
                    robot->turn_left();
                }
            }

        } else if (robot->m_position.second - path.back().second == -1) {
            while (robot->m_direction != 'n') {
                if (robot->m_direction == 'w') {
                    robot->turn_right();
                } else {
                    robot->turn_left();
                }
            }
        } else if (robot->m_position.second - path.back().second == 1) {
            while (robot->m_direction != 's') {
                if (robot->m_direction == 'e') {
                    robot->turn_right();
                } else {
                    robot->turn_left();
                }
            }
        }
        robot->move_forward();
    }
}

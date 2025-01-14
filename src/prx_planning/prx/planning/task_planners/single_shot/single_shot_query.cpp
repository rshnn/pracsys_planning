/**
 * @file single_shot_query.cpp
 * 
 * @copyright Software License Agreement (BSD License)
 * Copyright (c) 2013, Rutgers the State University of New Jersey, New Brunswick  
 * All Rights Reserved.
 * For a full description see the file named LICENSE.
 * 
 * Authors: Andrew Dobson, Andrew Kimmel, Athanasios Krontiris, Zakary Littlefield, Kostas Bekris 
 * 
 * Email: pracsys@googlegroups.com
 */

#include "prx/planning/task_planners/single_shot/single_shot_query.hpp"

#include <pluginlib/class_list_macros.h> 

PLUGINLIB_EXPORT_CLASS(prx::plan::single_shot_query_t, prx::plan::query_t)
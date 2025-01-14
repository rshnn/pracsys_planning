/**
 * @file grasping_planner.hpp
 *
 * @copyright Software License Agreement (BSD License)
 * Copyright (c) 2013, Rutgers the State University of New Jersey, New Brunswick
 * All Rights Reserved.
 * For a full description see the file named LICENSE.
 *
 * Authors: Andrew Dobson, Andrew Kimmel, Athanasios Krontiris, Zakary Littlefield, Rahul Shome, Kostas Bekris
 *
 * Email: pracsys@googlegroups.com
 */

#pragma once

#ifndef PRX_GRASPING_PLANNER_HPP
#define	PRX_GRASPING_PLANNER_HPP

#include "prx/utilities/definitions/defs.hpp"
#include "prx/utilities/parameters/parameter_reader.hpp"
#include "prx/utilities/definitions/sys_clock.hpp"
#include "prx/utilities/boost/hash.hpp"
#include "prx/utilities/math/configurations/config.hpp"
#include "prx/utilities/spaces/space.hpp"

#include "prx/simulation/plan.hpp"
#include "prx/simulation/trajectory.hpp"

#include "prx/planning/planner.hpp"
#include "prx/planning/problem_specifications/specification.hpp"
#include "prx/planning/queries/query.hpp"

#include "planning/manipulation_world_model.hpp"
#include "planning/queries/grasping_query.hpp"

namespace prx
{
    namespace packages
    {
        namespace manipulation
        {
            class grasp_entry_t
            {
                public:
                    grasp_entry_t(const util::config_t& conf, int open, int grasp)
                    {
                        relative_config = conf;
                        release_mode = open;
                        grasp_mode = grasp;
                    }

                    util::config_t relative_config;
                    int release_mode;
                    int grasp_mode;
            };

            /**
             * Manipulation task planner. Computes the path for moving an object from an
             * initial to a target position.
             *
             * @autors Athanasios Krontiris
             */
            class grasping_planner_t : public plan::planner_t
            {

              public:

                grasping_planner_t();
                virtual ~grasping_planner_t();

                virtual void init(const util::parameter_reader_t* reader, const util::parameter_reader_t* template_reader);

                /**
                 * @copydoc planner_t::reset()
                 */
                virtual void reset();

                /**
                 * @copydoc planner_t::link_world_model()
                 */
                virtual void link_world_model(plan::world_model_t * const model);

                /**
                 * @copydoc planner_t::get_statistics()
                 */
                virtual const util::statistics_t* get_statistics();

                /**
                 * @copydoc planner_t::link_specification(specification_t*)
                 */
                virtual void link_specification(plan::specification_t* new_spec);

                /**
                 * @copydoc planner_t::link_query()
                 */
                virtual void link_query(plan::query_t* new_query);

                /**
                 * @copydoc planner_t::setup()
                 */
                virtual void setup();

                /**
                 * @copydoc planner_t::execute()
                 */
                virtual bool execute();


                /**
                 * @copydoc planner_t::succeeded() const
                 */
                virtual bool succeeded() const;

                /**
                 * @copydoc planner_t::resolve_query()
                 */
                virtual void resolve_query();

                /** @copydoc planner_t::set_param(const std::string& , const std::string& , const boost::any& ) */
                virtual void set_param(const std::string& path, const std::string& parameter_name, const boost::any& value);

                virtual int nr_grasps(std::string context_name,movable_body_plant_t* object);            

              protected:

                virtual void evaluate_the_query(std::vector<grasp_entry_t>* type_grasps);

                /** @copydoc planner_t::set_param(const std::string&, const boost::any&) */
                virtual void set_param(const std::string& parameter_name, const boost::any& value);

                manipulation_world_model_t* manipulation_model;

                /** @brief Pointer to the current problem specification */
                plan::specification_t* input_specification;            

                grasping_query_t* grasping_query;

                /** @brief A map for the different types */
                util::hash_t<std::string, std::vector<grasp_entry_t> >  grasps;

                util::config_t retraction_config;

                std::string pracsys_path;
                std::vector<std::pair<std::string,std::string> > data_folders;

                sim::state_t* original_object_state;

            };
        }
    }
}


#endif

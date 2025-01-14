
(cl:in-package :asdf)

(defsystem "prx_simulation-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "graph_msg" :depends-on ("_package_graph_msg"))
    (:file "_package_graph_msg" :depends-on ("_package"))
    (:file "lqr_msg" :depends-on ("_package_lqr_msg"))
    (:file "_package_lqr_msg" :depends-on ("_package"))
    (:file "plan_msg" :depends-on ("_package_plan_msg"))
    (:file "_package_plan_msg" :depends-on ("_package"))
    (:file "state_msg" :depends-on ("_package_state_msg"))
    (:file "_package_state_msg" :depends-on ("_package"))
    (:file "plant_locations_msg" :depends-on ("_package_plant_locations_msg"))
    (:file "_package_plant_locations_msg" :depends-on ("_package"))
    (:file "control_msg" :depends-on ("_package_control_msg"))
    (:file "_package_control_msg" :depends-on ("_package"))
    (:file "bomberman_info_msg" :depends-on ("_package_bomberman_info_msg"))
    (:file "_package_bomberman_info_msg" :depends-on ("_package"))
    (:file "manipulation_acknowledgement" :depends-on ("_package_manipulation_acknowledgement"))
    (:file "_package_manipulation_acknowledgement" :depends-on ("_package"))
    (:file "query_msg" :depends-on ("_package_query_msg"))
    (:file "_package_query_msg" :depends-on ("_package"))
    (:file "world_config_msg" :depends-on ("_package_world_config_msg"))
    (:file "_package_world_config_msg" :depends-on ("_package"))
    (:file "interval_msg" :depends-on ("_package_interval_msg"))
    (:file "_package_interval_msg" :depends-on ("_package"))
  ))
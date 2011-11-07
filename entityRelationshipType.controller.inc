<?php

class EntityRelationshipTypeController extends DrupalDefaultEntityController{

  public function save($relationship_type) {
    
    // check if the relationship type object has a value for the rtid - if it does
    // we're updating an existing record so must pass the primary keys to 
    // drupal_write_record
    $primary_keys = array();
    if (isset($relationship_type->rtid)) {
      if (! empty($relationship_type->rtid)) {
        $primary_keys[] = 'rtid';
      }
    }
    
    // save the record
    drupal_write_record('entity_relationship_type', $relationship_type, $primary_keys);
    if (!empty($primary_keys)){
      field_attach_update('entity_relationship_type', $relationship_type);
    }
    else {
      field_attach_insert('entity_relationship_type', $relationship_type);
    }
    module_invoke_all('entity_insert', 'entity_relationship_type', $relationship_type);
    return $relationship_type;
  }
  
  public function delete($relationship_type) {
    $rtid = $relationship_type->rtid;
    $num_deleted = db_delete('entity_relationship_type')
      ->condition('rtid', $rtid)
      ->execute();
    return $num_deleted;
  }
  
  public function load_all() {
  
    $result = db_select('entity_relationship_type', 'ert')
    ->fields('ert')
    ->execute()
    ->fetchAll();
    
    return $result;
  }
  
}

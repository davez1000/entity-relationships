<?php

class EntityRelationshipController extends DrupalDefaultEntityController{

  public function save($relationship) {
    
    // check if the relationship object has a value for the rid - if it does
    // we're updating an existing record so must pass the primary keys to 
    // drupal_write_record
    $primary_keys = array();
    if (isset($relationship->rid)) {
      if (! empty($relationship->rid)) {
        $primary_keys[] = 'rid';
      }
    }
    
    // save the record
    drupal_write_record('entity_relationship', $relationship, $primary_keys);
    if (!empty($primary_keys)){
      field_attach_update('entity_relationship', $relationship);
    }
    else {
      field_attach_insert('entity_relationship', $relationship);
    }
    module_invoke_all('entity_insert', 'entity_relationship', $relationship);
    return $relationship;
  }
  
  public function delete($relationship) {
    $rid = $relationship->rid;
    $num_deleted = db_delete('entity_relationship')
      ->condition('rid', $rid)
      ->execute();
    return $num_deleted;
  }
  
  public function load_rids_by_node($nid) {
    $result = db_query("SELECT rid FROM {entity_relationship} WHERE source_id = :nid", array(':nid' => $nid));
    $rids = array();
    while ($record = $result->fetchObject()) {
      $rids[] = $record->rid;
    }
    return $rids;
  }
  
}

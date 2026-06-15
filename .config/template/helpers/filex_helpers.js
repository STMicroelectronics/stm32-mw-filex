/**
 * Helper functions for FileX schema.
 *
 * Goal: detect which LevelX interface is selected without relying on a fixed index in LevelX interfaces[].
 */

function extractInterfaceTypeFromEntry(entry) {
  if (!entry || typeof entry !== "object") {
    return undefined;
  }
  const logical = entry.logical_config;
  if (!logical || typeof logical !== "object") {
    return undefined;
  }
  const itf = logical.interface_type;
  return typeof itf === "string" ? itf : undefined;
}

/**
 * Accepts either:
 * - the full array returned by $get(..., '/interfaces')
 * - an object containing { interfaces: [...] }
 * - a string returned by $get(..., 'interface_type') as fallback
 */
function levelxHasInterfaceType(levelxInterfaceConfigOrValue, expectedInterfaceType) {
  if (typeof expectedInterfaceType !== "string" || expectedInterfaceType.length === 0) {
    return false;
  }

  // Fallback: some environments might return a direct string (non-array)
  if (typeof levelxInterfaceConfigOrValue === "string") {
    return levelxInterfaceConfigOrValue === expectedInterfaceType;
  }

  let array = levelxInterfaceConfigOrValue;
  if (array && typeof array === "object" && !Array.isArray(array) && Array.isArray(array.interfaces)) {
    array = array.interfaces;
  }

  if (!Array.isArray(array)) {
    return false;
  }

  for (let i = 0; i < array.length; i++) {
    const currentType = extractInterfaceTypeFromEntry(array[i]);
    if (currentType === expectedInterfaceType) {
      return true;
    }
  }

  return false;
}

/**
 * Returns true when at least one FileX interface has the requested interface_type.
 *
 * Accepts either:
 * - the full array returned by $get(..., 'interfaces')
 * - an object containing { interfaces: [...] }
 */
function filexHasInterfaceType(filexInterfaceConfigOrValue, expectedInterfaceType) {
  if (typeof expectedInterfaceType !== "string" || expectedInterfaceType.length === 0) {
    return false;
  }

  let array = filexInterfaceConfigOrValue;
  if (array && typeof array === "object" && !Array.isArray(array) && Array.isArray(array.interfaces)) {
    array = array.interfaces;
  }

  if (!Array.isArray(array)) {
    return false;
  }

  for (let i = 0; i < array.length; i++) {
    const currentType = extractInterfaceTypeFromEntry(array[i]);
    if (currentType === expectedInterfaceType) {
      return true;
    }
  }

  return false;
}

module.exports = {
  filexHasInterfaceType,
  levelxHasInterfaceType,
};

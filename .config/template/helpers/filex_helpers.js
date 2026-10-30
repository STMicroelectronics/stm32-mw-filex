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

function extractHwSelectionFromEntry(entry) {
  try {
    if (!entry || typeof entry !== "object") {
      return "";
    }

    const resources = entry.resources_allocation;
    if (!resources || typeof resources !== "object") {
      return "";
    }

    const hwSelection = resources.hw_selection;

    // bind.peripheral.config usually stores an object with a `selection` key.
    if (hwSelection && typeof hwSelection === "object") {
      const selected = hwSelection.selection;
      return typeof selected === "string" ? selected : "";
    }

    // Keep compatibility if value is persisted as a plain string.
    return typeof hwSelection === "string" ? hwSelection : "";
  } catch (error) {
    return "";
  }
}

function extractMemorySelectionFromEntry(entry) {
  if (!entry || typeof entry !== "object") {
    return "";
  }

  const resources = entry.resources_allocation;
  if (!resources || typeof resources !== "object") {
    return "";
  }

  const memorySelection = resources.memory_selection;
  return typeof memorySelection === "string" ? memorySelection : "";
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

/**
 * Counts how many FileX interfaces currently use the requested interface_type.
 *
 * Accepts either:
 * - the full array returned by $get(..., 'interfaces')
 * - an object containing { interfaces: [...] }
 */
function filexCountInterfaceType(filexInterfaceConfigOrValue, expectedInterfaceType) {
  if (typeof expectedInterfaceType !== "string" || expectedInterfaceType.length === 0) {
    return 0;
  }

  let array = filexInterfaceConfigOrValue;
  if (array && typeof array === "object" && !Array.isArray(array) && Array.isArray(array.interfaces)) {
    array = array.interfaces;
  }

  if (!Array.isArray(array)) {
    return 0;
  }

  let count = 0;
  for (let i = 0; i < array.length; i++) {
    if (extractInterfaceTypeFromEntry(array[i]) === expectedInterfaceType) {
      count++;
    }
  }

  return count;
}

/**
 * Returns true when a specific resource value is already used by another compatible interface.
 *
 * Groups:
 * - SD_ITF/MMC_ITF use resources_allocation.hw_selection.selection
 * - NOR_ITF/NAND_ITF use resources_allocation.memory_selection
 */
function filexIsResourceValueUsedByOtherInterface(filexInterfaceConfigOrValue, currentItem, selectedValue) {
  let array = filexInterfaceConfigOrValue;
  if (array && typeof array === "object" && !Array.isArray(array) && Array.isArray(array.interfaces)) {
    array = array.interfaces;
  }

  if (
    !Array.isArray(array) ||
    !currentItem ||
    typeof currentItem !== "object" ||
    typeof selectedValue !== "string" ||
    selectedValue.length === 0
  ) {
    return false;
  }

  const currentType = extractInterfaceTypeFromEntry(currentItem);
  const currentIsSdOrMmc = currentType === "SD_ITF" || currentType === "MMC_ITF";
  const currentIsNorOrNand = currentType === "NOR_ITF" || currentType === "NAND_ITF";

  if (!currentIsSdOrMmc && !currentIsNorOrNand) {
    return false;
  }

  for (let i = 0; i < array.length; i++) {
    const currentEntry = array[i];
    if (currentItem && currentEntry === currentItem) {
      continue;
    }

    const interfaceType = extractInterfaceTypeFromEntry(currentEntry);
    const isSdOrMmc = interfaceType === "SD_ITF" || interfaceType === "MMC_ITF";
    const isNorOrNand = interfaceType === "NOR_ITF" || interfaceType === "NAND_ITF";

    if (currentIsSdOrMmc && isSdOrMmc && extractHwSelectionFromEntry(currentEntry) === selectedValue) {
      return true;
    }

    if (currentIsNorOrNand && isNorOrNand && extractMemorySelectionFromEntry(currentEntry) === selectedValue) {
      return true;
    }
  }

  return false;
}

module.exports = {
  filexHasInterfaceType,
  levelxHasInterfaceType,
  filexCountInterfaceType,
  filexIsResourceValueUsedByOtherInterface,
};

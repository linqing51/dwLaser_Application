export const language: string;
export const isChinese: boolean;
export const messages: Record<string, string>;
export function translate(key: string, locale?: string, values?: (string | number | undefined)[]): string;
export function t(key: string, ...values: (string | number | undefined)[]): string;

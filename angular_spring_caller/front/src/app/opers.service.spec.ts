import { TestBed } from '@angular/core/testing';

import { OpersService } from './opers.service';

describe('OpersService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: OpersService = TestBed.get(OpersService);
    expect(service).toBeTruthy();
  });
});
